#include "SystemIO.hpp"

SystemIO::SystemIO()
{

}

SystemIO::SystemIO(std::shared_ptr<std::stack<Object>> &_stack_ptr)
{
	init = bind_stack(_stack_ptr);
}

bool SystemIO::bind_stack(std::shared_ptr<std::stack<Object>> &_stack_ptr)
{
	if (_stack_ptr == nullptr)
	{
		logger.elog("io error: failed to initialize io system.");
		return false;
	}
	stack_ptr = _stack_ptr;
	return true;
}

void SystemIO::run_opcode(byte opcode, DracheVM &vm)
{
	if (!init)
	{
		logger.elog("io error: opcode called when io system not initialized.");
		return;
	}
	Object obj_buff;
	obj_buff.set_i64(0x00000000);

	//	TODO: Add ability to print things in hex, octal, and binary by changing the stream type through opcodes.
	//	Also add the ability to not pop objects off of the stack when you want. Also controlled by an opcode.

	switch (opcode)
	{
	case PRINTNL:
		printf("\n");
		break;
	case PRINTCHR:
		printf("%c", vm.get_stack().top().get_i8());
		vm.get_stack().pop();
		break;
	case PRINTSTR:
		printf("%s", vm.get_stack().top().get_str());
		delete[] (vm.get_stack().top().get_str());	//	Deallocate the string before popping it.
		vm.get_stack().pop();
		break;
	case PRINTINT8:
		printf("%d", vm.get_stack().top().get_i8());
		vm.get_stack().pop();
		break;
	case PRINTINT16:
		printf("%d", vm.get_stack().top().get_i16());
		vm.get_stack().pop();
		break;
	case PRINTINT32:
		printf("%d", vm.get_stack().top().get_i32());
		vm.get_stack().pop();
		break;
	case PRINTINT64:
		printf("%ld", (long)vm.get_stack().top().get_i64());
		vm.get_stack().pop();
		break;
	case PRINTF32:
		printf("%f", vm.get_stack().top().get_f32());
		vm.get_stack().pop();
		break;
	case PRINTF64:
		printf("%f", vm.get_stack().top().get_f64());
		vm.get_stack().pop();
		break;
	case READCHR:
		// Note: Add the allocation for a character on the stack next time you work on this.
		// Since this isn't complete, I'll leave it for now. You need space allocation for strings set up first.
		// scanf("%c", obj_buff.str);
		vm.get_stack().push(obj_buff);
		break;
	}
}


SystemIO::~SystemIO()
{
}
