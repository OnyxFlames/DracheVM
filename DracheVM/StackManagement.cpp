#include "StackManagement.hpp"
#include "Opcodes.hpp"

#include <iostream>
#include <vector>
#include <cstring>

#define DEBUG(x) std::cout << "DEBUG: " << x << std::endl;



extern Logger logger;

void push_to_stack(DracheVM &vm)
{
	Object object_buffer;
	object_buffer.i64 = 0;	// Clear the buffer to 0. This is to guarantee that when pushing values smaller than 64 bits onto the stack, they aren't corrupted with garbage data.
	byte variable_size = vm.next();
	if (variable_size == 1)	//char*
	{
		/*// Load a null-terminated(C-string) into a vector
		std::vector<char> byte_buff;
		// Unfortunately we need to have this buffer to be a vector of char's instead of actual byte's so that str_buff doesn't complain.
		byte buff = vm.next();
		while (buff != '\0')
		{
			byte_buff.push_back(buff);
			buff = vm.next();
		}
		// After reaching the terminater, append the '\0'.
		byte_buff.push_back(0x00);
		// Create the string buffer and populate it with byte_buff's content.
		std::string str_buff(byte_buff.data(), byte_buff.size());
		// Copy the contents of the str_buff(as a char*) onto the object buffer and push the object buffer onto the vm's stack.*/
		std::strcpy(object_buffer.str,
								from_c_str(vm)	// This reads bytes until it reaches a null byte, casts it into a byte array, then puts that byte array into a std::string. Returns said string.
											.c_str());
		vm.get_stack().push(object_buffer);
	}
	else if (variable_size == 2)
	{
		object_buffer.i8 = vm.next();
		vm.get_stack().push(object_buffer);
	}

	else if (variable_size == 3)
	{
		uint16_t buffer = 0;
		for (int c = 0; c < 3; c++)
		{
			buffer += vm.next();
			buffer <<= 8;
		}
		buffer += vm.next();
		object_buffer.i16 = buffer;
		vm.get_stack().push(object_buffer);
	}
	else if (variable_size == 4)
	{
		uint32_t buffer = 0;
		for (int c = 0; c < 3; c++)
		{
			buffer += vm.next();
			buffer <<= 8;
		}
		buffer += vm.next();
		object_buffer.i32 = buffer;
		vm.get_stack().push(object_buffer);
	}
	else if (variable_size == 5)
	{
		uint64_t buffer = 0;
		for (int c = 0; c < 7; c++)
		{
			buffer += vm.next();
			buffer <<= 8;
		}
		buffer += vm.next();
		object_buffer.i64 = buffer;
		vm.get_stack().push(object_buffer);
	}
	else if (variable_size == 6)
	{
		// Floating point literals are going to be loaded similar to C-strings, except they will be casted into either a float or a double afterwards.
		// This is due to how floating point values are stored in memory as fractions, making loading them byte by byte rather difficult.
		// For documentation on what this execution branch is doing refer the from_c_str(DracheVM &vm) function in Misc_Utils.cpp

		object_buffer.f32 = (float)atof(from_c_str(vm).c_str());
		vm.get_stack().push(object_buffer);
	}
	else if (variable_size == 7)
	{
		object_buffer.f64 = atof(from_c_str(vm).c_str());
		vm.get_stack().push(object_buffer);
	}
	else
	{
		if (variable_size > 0)
			std::cerr << "vm error: variable type " << variable_size << " at location " << vm.get_state().current_position << " is not supported(1 - 7). Exiting." << std::endl;
		else
			std::cerr << "vm error: variable type UNKNOWN at location " << vm.get_state().current_position << " is not supported(1 - 7). Exiting." << std::endl;
	}
}

void pop_to_register(uint8_t register_index, DracheVM &vm)
{
	if (vm.get_stack().empty())
	{
		logger.elog("vm error: attempted to pop from empty stack!");
		return;
	}

	register_index--; // Registers are passed 1-based. Decrement to get the actual register.
	vm.get_register(register_index) = vm.get_stack().top();
	vm.get_stack().pop();
}

void push_from_register(uint8_t register_index, DracheVM &vm) 
{
	register_index--; // Registers are passed 1-based. Decrement to get the actual register.
	vm.get_stack().push(vm.get_register(register_index));
	vm.get_register(register_index).i64 = 0; // Clear the register after adding its value back onto the stack.
}

void move_to_register(uint8_t register_from, uint8_t register_to, DracheVM &vm)
{
	// Decrement registers for actual values.
	register_from--;
	register_to--;
	// Move the data from the FROM register to the TO register.
	vm.get_register(register_to).i64 = vm.get_register(register_from).i64;
	vm.get_register(register_from).i64 = 0x00;	// Clear the FROM registers contents.
}
