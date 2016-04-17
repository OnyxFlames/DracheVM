#ifndef SYSTEMIO_HPP
#define SYSTEMIO_HPP

#include <memory>
#include <stack>
#include <string>
#include <vector>
#include "Logger.hpp"
#include "Object.hpp"
#include "Opcodes.hpp"
#include "DracheVM.hpp"

extern Logger logger;

/*
	IO Static System Class.
	This class is initialized on the heap, and is handles using the SYSCALL opcode, followed by the identifier(0x01 in this case), then the command.
	The command opcodes are dictated by the IO_OPCODES enum.
*/

enum IO_OPCODES
{
	// Print the value on the top of the stack from stdout. Pop it afterwards.
	PRINTNL = 01,
	PRINTSTR = 02,
	PRINTCHR,
	PRINTINT8,
	PRINTINT16,
	PRINTINT32,
	PRINTINT64,


	// Read the value from stdin and push it onto the stack.
	READSTR,
	READCHR,
	READINT8,
	READINT16,
	READINT32,
	READINT64
};

class SystemIO
{
private:
	bool init = false;
	std::shared_ptr<std::stack<Object>> stack_ptr;
public:
	SystemIO();
	SystemIO(std::shared_ptr<std::stack<Object>> &_stack_ptr);
	bool bind_stack(std::shared_ptr<std::stack<Object>> &_stack_ptr);
	void run_opcode(byte opcode, DracheVM &vm);
	~SystemIO();
};

#endif
