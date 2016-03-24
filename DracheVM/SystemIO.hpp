#pragma once

#include <memory>
#include <stack>
#include <string>
#include <vector>
#include "Logger.hpp"
#include "Object.hpp"

extern Logger logger;

/*
	IO Static System Class.
	This class is initialized on the heap, and is handles using the SYSCALL opcode, followed by the identifier(0x01 in this case), then the command.
	The command opcodes are dictated by the IO_OPCODES enum.
*/

enum IO_OPCODES
{
	// Print the value on the top of the stack from stdout. Pop it afterwards.
	PRINTSTR = 01,
	PRINTCHR,
	PRINTINT,


	// Read the value from stdin and push it onto the stack.
	READSTR,
	READCHR,
	READINT,
};

class SystemIO
{
private:
	std::unique_ptr<std::stack<Object>> stack_ptr;
public:
	SystemIO(std::unique_ptr<std::stack<Object>> &_stack_ptr);
	~SystemIO();
};

