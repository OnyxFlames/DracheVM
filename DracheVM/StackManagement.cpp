#include "StackManagement.hpp"
#include "Opcodes.hpp"

#include <iostream>

#define DEBUG(x) std::cout << "DEBUG: " << x << std::endl;

extern Logger logger;

void push_to_stack(DracheVM &vm)
{
	Object object_buffer;
	object_buffer.i64 = 0;	// Clear the buffer to 0. This is to guarantee that when pushing values smaller than 64 bits onto the stack, they aren't corrupted with garbage data.
	byte variable_size = vm.next();
	
	if (variable_size == 1)	//char*
	{

		//TODO: Add string constant loading.
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
	else if (variable_size == 6 || variable_size == 7)
	{
		std::cerr << "vm error: floating point literals are yet to be supported. Exiting." << std::endl;
		std::exit(-1);
	}
	else
		std::cerr << "vm error: variable type " << variable_size << " at location " << vm.get_state().current_position << " is not supported(1 - 7). Exiting." << std::endl;
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