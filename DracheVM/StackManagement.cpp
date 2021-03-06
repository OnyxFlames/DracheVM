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
	object_buffer.set_i64(0);	// Clear the buffer to 0. This is to guarantee that when pushing values smaller than 64 bits onto the stack, they aren't corrupted with garbage data.
	byte variable_size = vm.next();
	if (variable_size == 1)	// char*
	{
		std::strcpy(object_buffer.get_str(),
								from_c_str(vm)	// This reads bytes until it reaches a null byte, casts it into a byte array, then puts that byte array into a std::string. Returns said string.
											.c_str());
		vm.get_stack().push(object_buffer);
	}
	else if (variable_size == 2)
	{
		object_buffer.set_i8(vm.next());
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
		object_buffer.set_i16(buffer);
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
		object_buffer.set_i32(buffer);
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
		object_buffer.set_i64(buffer);
		vm.get_stack().push(object_buffer);
	}
	else if (variable_size == 6)
	{
		// Floating point literals are going to be loaded similar to C-strings, except they will be casted into either a float or a double afterwards.
		// This is due to how floating point values are stored in memory as fractions, making loading them byte by byte rather difficult.
		// For documentation on what this execution branch is doing refer the from_c_str(DracheVM &vm) function in Misc_Utils.cpp

		object_buffer.set_f32
		(
			(
				(float)atof(from_c_str(vm).c_str())
			)
		);
		vm.get_stack().push(object_buffer);
	}
	else if (variable_size == 7)
	{
		object_buffer.set_f64
		(
			(
				atof(from_c_str(vm).c_str())
			)
		);
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
	vm.get_register(register_index).set_i64(0); // Clear the register after adding its value back onto the stack.
}

void move_to_register(uint8_t register_from, uint8_t register_to, DracheVM &vm)
{
	// Decrement registers for actual values.
	register_from--;
	register_to--;
	// Move the data from the FROM register to the TO register.
	vm.get_register(register_to).set_i64((vm.get_register(register_from).get_i64()));
	vm.get_register(register_from).set_i64(0x00);	// Clear the FROM registers contents.
}
