#include "Syscall.hpp"

/*
	Syscall.cpp
	This function sorts system calls, and calls the appropriate static system to handle the code.
*/

void syscall(byte system, byte code, DracheVM &vm)
{
	if (system == IO)
	{
		io->run_opcode(code, vm);
	}
	else if (system == RANDNUMGEN)
	{
		rng->run_opcode(code, vm);
	}
	else
	{
		logger.elog("syscall error: static system id not found! Exiting.");
		std::exit(-1);
	}
}
