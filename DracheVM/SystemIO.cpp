#include "SystemIO.hpp"



SystemIO::SystemIO(std::unique_ptr<std::stack<Object>> &_stack_ptr)
{
	if (stack_ptr == nullptr)
	{
		logger.elog("io error: failed to initialize io system");
	}
}


SystemIO::~SystemIO()
{
}
