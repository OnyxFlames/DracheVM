#include "DracheVM.hpp"
#include "StackManagement.hpp"
#include "VariableManip.hpp"
#include "Syscall.hpp"
#include "Misc_Utils.hpp"

#include <bitset>

extern Logger logger;

DracheVM::DracheVM() {}

#define DEBUG(x) std::cout << "DEBUG: " << x << std::endl;

DracheVM::DracheVM(const std::string filelocation)
{
	std::cout << "DEBUG: " << ROM.size() << "\n";
	open(filelocation);
}

void DracheVM::open(std::string filelocation)
{
	file.open(filelocation, std::ios::binary);
	if (!file.is_open())
	{
		std::cerr << "vm error: failed to load file. Exiting." << std::endl;
		std::exit(-1);
	}
	state.is_open = true;
	if (get_rom_size() < max_rom_size)	// Modify DracheVM::run() to return bytes from either memory or the ROM. Prioritize reading from memory, as it is faster.
		load_into_memory();
	run();
}

void DracheVM::run()
{
	// Pre-run set up.
	clear_registers(_register);

	while (state.is_open)	// TODO: Have opcodes aware of the VM's state. eg. if it hits an exit make sure to change it to state.is_open = false;
	{
		byte byte_buff[2]{ 0 };
		Object object_buffer[2]; 
		object_buffer[0].set_i64(0);	// Clear the buffer to 0. This is to guarantee that when pushing values smaller than 64 bits onto the stack, they aren't corrupted with garbage data.
		object_buffer[1].set_i64(0);
		int val = next();
		switch (val)
		{
		case NOP:
			// Do nothing.
			break;
		case PUSH:
			jump();
			push_to_stack(*this);
			restore();
			rel_jump(0x02);
			break;
		case POP:
			if (stack.empty())
			{
				logger.elog("vm error: attempted to pop from empty stack!");
				break;
			}
			stack.pop();
			break;
		case MOV:
			byte_buff[0] = next();
			byte_buff[1] = next();
			if (is_in_range(0x00, 0x04, (int64_t)byte_buff[0]))
			{
				if (byte_buff[0] == 0x00 && is_in_range(0x01, 0x04, (int64_t)byte_buff[1]))	// if the mov is FROM the stack TO a register.
					pop_to_register(byte_buff[1], *this);

				if (is_in_range(0x01, 0x04, (int64_t)byte_buff[0]) && byte_buff[1] == 0x00)
					push_from_register(byte_buff[0], *this);

				if (is_in_range(0x01, 0x04, (int64_t)byte_buff[0]) && is_in_range(0x01, 0x04, (int64_t)byte_buff[1]))
					move_to_register(byte_buff[0], byte_buff[1], *this);
			}
			else
			{
				logger.elog("vm error: invalid MOV operation! Skipping..");
			}
			break;
		case ROT:
			if (stack.size() < 2)
			{
				logger.elog("vm error: attempted to rotate on empty stack.");
				break;
			}
			//Object buffer[2];
			object_buffer[0] = stack.top();
			stack.pop();
			object_buffer[1] = stack.top();
			stack.pop();
			stack.push(object_buffer[0]);
			stack.push(object_buffer[1]);
			break;
		case ADD8: case SUB8: case MUL8: case DIV8:
		case ADD16: case SUB16: case MUL16: case DIV16:
		case ADD32: case SUB32: case MUL32: case DIV32:
		case ADD64: case SUB64: case MUL64: case DIV64:
		case ADDF32: case SUBF32: case MULF32: case DIVF32:
		case ADDF64: case SUBF64: case MULF64: case DIVF64:
			variable_handler(val, *this);
			break;
		case SYSCALL:
			byte_buff[0] = next();
			byte_buff[1] = next();
			syscall(byte_buff[0], byte_buff[1], *this);
			break;
		case GOTO:
			byte_buff[0] = next();
			byte_buff[1] = next();
			jump
				(assemble_16bit_address
					(byte_buff[0], byte_buff[1]));
			break;
		case EQGOTO:
			object_buffer[0] = stack.top();
			stack.pop();
			// compare the top two values on the stack as their pure 64-bit wide values.
			if (object_buffer[0].get_i64() == stack.top().get_i64())
			{
				stack.pop();
				byte_buff[0] = next();
				byte_buff[1] = next();
				jump
					(assemble_16bit_address
						(byte_buff[0], byte_buff[1]));
			}
			else
			{
				// Skip the address and continue executing code below.
				rel_jump(0x02);
			}
			break;
		case SETERR:
			byte_buff[0] = next();
			byte_buff[1] = next();
			state.error_flag = assemble_16bit_address(byte_buff[0], byte_buff[1]);
			if (state.error_flag == 0x0000)
				state.is_error_state = false;
			else
				state.is_error_state = true;
			break;
		case EXIT:
			// equivalent to state.is_open = false;
			vm_exit();
			break;
		default:
			logger.elog("vm error: read unknown byte. rom could be corrupted!");
		}
		
		if (trace)
		{
			if (val <= TOTAL_OPCODES)
				std::cout << "\nCallstack: [" << opcode_strs[val] << "]\n";
			else
				std::cout << "\nCallstack: [" << std::hex << val  << std::dec << "]\n";
		}
		
	}
}

Object &DracheVM::get_register(uint8_t register_index)
{
	if (register_index > 3)
	{
		std::cerr << "vm error: attempted to access non-existent register! Exiting." << std::endl;
		std::exit(-1);
	}
	return _register[register_index];
}

std::stack<Object> &DracheVM::get_stack() 
{
	return stack;
}

inline int DracheVM::next()
{
	if (in_memory)
		return ROM[index++];
	else
		return file.get();
}

void DracheVM::rel_jump(int32_t jump_distance)
{
	if (in_memory)
		index = index + jump_distance;
	else
		file.seekg(file.tellg() + (std::streampos)jump_distance);
}

void DracheVM::jump(int32_t jump_address)	// Have the VM's pointer jump to a different part of the ROM.
											// This function reads the next two bytes, constructs a 16 bit address, and goes to it.
{											// The jump_address defaults to -1, if it is still -1 when the function is called it reads the next two bytes. Otherwise it goes to that address.
	if (jump_address == -1)
	{
		if (in_memory)
			address = index;
		else
			address = (uint16_t)file.tellg();
		
		uint16_t _jump_address = 0;

		_jump_address += (byte)next();
		_jump_address <<= 8;
		_jump_address += (byte)next();
		
		if (in_memory)
			index = _jump_address;
		else
			file.seekg(_jump_address);
	}
	else
	{
		if (in_memory)
			index = jump_address;
		else
			file.seekg(jump_address);
	}
}

void DracheVM::restore()
{
	if (in_memory)
		index = address;
	else
		file.seekg(address);

	address = 0x0000;
}

vm_state& DracheVM::get_state()
{
	if (in_memory)
		state.current_position = index;
	else
		state.current_position = (uint32_t)file.tellg();	// Update the state before returning it.
	return state;
}

void DracheVM::vm_exit()
{
	//stack_dump();
	//std::exit(1);
	state.is_open = false;
	if (state.is_error_state)
	{
		std::cout << "\n\nSystem exited with error code: " << state.error_flag << "\n";
		stack_dump();
	}
}
void DracheVM::stack_dump()
{
	std::cout << "Registers:\n";
	std::cout << "HEX - DEC\n";
	for (unsigned i = 0; i < 4; i++)
	{
		std::cout << std::hex << _register[i].get_i64() << " - " << std::dec << _register[i].get_i64() << "\n";
	}
	std::cout << "Stack Dump(" << stack.size() << "):\n";
	std::cout << "HEX - DEC\n";
	while (!stack.empty())
	{
		std::cout << std::hex << stack.top().get_i64() << " - " << std::dec << stack.top().get_i64() << "\n";
		stack.pop();
	}

	logger.log("Exit called. Closing VM.");
	file.close();
	state.is_open = false;
	state.current_position = 0x00000000;
	for (int i = 0; i < 4; i++)
		_register[i].set_i64(0x00);
	while (!stack.empty())
		stack.pop();

	if (in_memory)
	{
		std::cout << "\nDumping internal ROM state to DUMP.dvm!\n";
		std::ofstream dump("DUMP.dvm");
		if (!dump.is_open())
			logger.elog("stack dump error: unable to dump internal ROM state to DUMP.dvm... something has gone horribly wrong.\n");
		for (uint32_t dump_iter = 0; dump_iter < max_rom_size; dump_iter++)
			dump << ROM[dump_iter];
	}
}

DracheVM* DracheVM::get_vm()
{
	/*
		TODO: Add private functions to copy over all of the vms internal state over to a temporary one, then return that temporary one.
		This will be used to clone VM's.
	*/
	return this;
}

size_t DracheVM::get_rom_size()
{
	size_t ret = 0;
	file.seekg(0, std::ios::end);
  //file.seekg(std::ios::end);	The above version of the function returns the rom size much more accurately by including the file offset(defaults at 0).
	ret = (size_t)file.tellg();
	file.seekg(0, std::ios::beg);
	return ret;
}

void DracheVM::load_into_memory()
{
	size_t rom_size = get_rom_size();
	for (unsigned i = 0; i < rom_size; i++)
	{
		ROM[i] = file.get();
	}
	// Safe-measure to make sure that if the rom jumps to the wrong part in memory that it will reach an exit call.
	for (size_t i = rom_size; i < max_rom_size; i++)
		ROM[i] = NOP;
	in_memory = true;
}

DracheVM::~DracheVM()
{
	/* This isnt used anymore as the state is set to closed on the exit call.
	if (state.is_open) 
	{
		std::cout << "Registers:\n";
		for (unsigned i = 0; i < 4; i++)
		{
			std::cout << std::hex << _register[i].i64 << "\n";
		}
		std::cout << "Stack Dump(" << stack.size() << "):\n";
		while (!stack.empty())
		{
			std::cout << std::hex << stack.top().i64 << "\n";
			stack.pop();
		}
	}
	*/
}
