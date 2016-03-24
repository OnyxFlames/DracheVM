#include "DracheVM.hpp"
#include "Opcodes.hpp"
#include "StackManagement.hpp"

extern Logger logger;

DracheVM::DracheVM() {}

#define DEBUG(x) std::cout << "DEBUG: " << x << std::endl;

DracheVM::DracheVM(const std::string filelocation)
{
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
	run();
}

void DracheVM::run()
{
	while (!file.eof() && !file.fail())
	{
		Object object_buffer; 
		object_buffer.i64 = 0;	// Clear the buffer to 0. This is to guarantee that when pushing values smaller than 64 bits onto the stack, they aren't corrupted with garbage data.
		switch (file.get())
		{
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
		case POP1:
			pop_to_register(0x01, *this);
			break;
		case POP2:
			pop_to_register(0x02, *this);
			break;
		case POP3:
			pop_to_register(0x03, *this);
			break;
		case POP4:
			pop_to_register(0x04, *this);
			break;
		case PUSH1:
			push_from_register(0x01, *this);
			break;
		case PUSH2:
			push_from_register(0x02, *this);
			break;
		case PUSH3:
			push_from_register(0x03, *this);
			break;
		case PUSH4:
			push_from_register(0x04, *this);
			break;
		case ROT:
			if (stack.size() < 2)
			{
				logger.elog("vm error: attempted to rotate on empty stack.");
				break;
			}
			Object buffer[2];
			buffer[0] = stack.top();
			stack.pop();
			buffer[1] = stack.top();
			stack.pop();
			stack.push(buffer[0]);
			stack.push(buffer[1]);
			break;
		case EXIT:
			vm_exit();
			break;
		default:
			logger.elog("vm error: read unknown byte. rom could be corrupted!");
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

int DracheVM::next()
{
	return file.get();
}

void DracheVM::rel_jump(int32_t jump_distance)
{
	file.seekg(file.tellg() + (std::streampos)jump_distance);
}

void DracheVM::jump(int32_t jump_address)	// Have the VM's pointer jump to a different part of the ROM.
											// This function reads the next two bytes, constructs a 16 bit address, and goes to it.
{											// The jump_address defaults to -1, if it is still -1 when the function is called it reads the next two bytes. Otherwise it goes to that address.
	if (jump_address == -1)
	{

		address = (uint16_t)file.tellg();
		uint16_t jump_address = 0;
		/*
		For some reason this was set to loop 3 times. I'll remove this once I figure out why it was set to do that.
		for (int c = 0; c < 3; c++)
		{*/
		jump_address += file.get();
		jump_address <<= 8;
		//}
		jump_address += file.get();
		file.seekg(jump_address);
	}
	else
	{
		file.seekg(jump_address);
	}
}

void DracheVM::restore()
{
	file.seekg(address);
	address = 0x0000;
}

vm_state DracheVM::get_state()
{
	state.current_position = (uint32_t)file.tellg();	// Update the state before returning it.
	return state;
}

void DracheVM::vm_exit()
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

	logger.log("Exit called. Closing VM");
	file.close();
	state.is_open = false;
	state.current_position = 0x00000000;
	for (int i = 0; i < 4; i++)
		_register[i].i64 = 0x00;
	while (!stack.empty())
		stack.pop();

	std::exit(1);
}

DracheVM::~DracheVM()
{
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
}
