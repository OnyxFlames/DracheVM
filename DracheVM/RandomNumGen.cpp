#include "RandomNumGen.hpp"
#include <ctime>

RandomNumGen::RandomNumGen()
{

}

RandomNumGen::RandomNumGen(std::shared_ptr<std::stack<Object>> &_stack_ptr)
{
	init = bind_stack(_stack_ptr);	
}

bool RandomNumGen::bind_stack(std::shared_ptr<std::stack<Object>> &_stack_ptr)
{
	if (_stack_ptr == nullptr)
	{
		logger.elog("rng error: failed to initialize random number generator.");
		return false;
	}
	stack_ptr = _stack_ptr;
	return true;
}

void RandomNumGen::run_opcode(byte opcode, DracheVM &vm)
{
	if (!init)
	{
		logger.elog("rng error: opcode called when rng system not initialized.");
		return;
	}
	switch (opcode)
	{
	case SETSEED:
		_seed = vm.get_stack().top().i32;
		break;
	}
}

double RandomNumGen::generate(double min, double max)
{
	//TODO: FIX
	return 0;
}

RandomNumGen::~RandomNumGen()
{
}
