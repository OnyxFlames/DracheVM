#include "DracheVM.hpp"
#include "Opcodes.hpp"
#include "StackManagement.hpp"


extern Logger logger;

DracheVM::DracheVM(const std::string filelocation)
{
	file.open(filelocation, std::ios::binary);
	if (!file.is_open())
	{
		std::cerr << "vm error: failed to load file. Exiting." << std::endl;
		std::exit(-1);
	}
	run();
}


void DracheVM::run()
{
	
	while (!file.eof())
	{
		Object object_buffer; 
		object_buffer.i64 = 0;	// Clear the buffer to 0. This is to guarantee that when pushing values smaller than 64 bits onto the stack, they aren't corrupted with garbage data.
		switch (file.get())
		{
		case PUSH:
			push_to_stack(file, stack);
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

DracheVM::~DracheVM()
{
}
