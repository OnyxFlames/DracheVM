#include "Decompiler.hpp"
#include "Logger.hpp"

#include <iomanip>

extern Logger logger;
Decompiler::Decompiler() { }
Decompiler::Decompiler(std::string _input, std::string _output)
	: input(_input), output(_output)
{
	if (!input.is_open())
	{
		logger.elog("decompile error: unable to open input file to decompile. Exiting..");
		std::exit(-1);
	}
	if (!output.is_open())
	{
		logger.elog("decompile error: unable to create output file for decompile. Exiting..");
		std::exit(-1);
	}
	run();
}
void Decompiler::open(std::string _input, std::string _output)
{
	input.open(_input);
	output.open(_output);

	if (!input.is_open())
	{
		logger.elog("decompile error: unable to open input file to decompile. Exiting..");
		std::exit(-1);
	}
	if (!output.is_open())
	{
		logger.elog("decompile error: unable to create output file for decompile. Exiting..");
		std::exit(-1);
	}
}
void Decompiler::run()
{
	uint16_t buff;
	while (!input.eof())
	{
		buff = input.get();

		switch (buff)
		{
		case NOP:
			output << "NOP(0x00)\n";
			break;
		case PUSH:
			output << "PUSH(0x01)\n";
			break;
		case POP:
			output << "POP(0x02)\n";
			break;
		case ALLOC:
			output << "ALLOC(0x03)\n";
			break;
		case DEALLOC:
			output << "DEALLOC(0x04)\n";
			break;
		case ROT:
			output << "ROT(0x05)\n";
			break;
		case MOV:
			output << "MOV(0x06)\n";
			break;
		case ADD8: case SUB8: case MUL8: case DIV8:
		case ADD16: case SUB16: case MUL16: case DIV16:
		case ADD32: case SUB32: case MUL32: case DIV32:
		case ADD64: case SUB64: case MUL64: case DIV64:
		case ADDF32: case SUBF32: case MULF32: case DIVF32:
		case ADDF64: case SUBF64: case MULF64: case DIVF64:
			output << "VAR_MANIP(0x" << std::hex << std::setfill('0') << std::setw(2) << buff << std::dec << ")\n";
			break;
		case GOTO:
			output << "GOTO(0x3D)\n";
			break;
		case EQGOTO:
			output << "EQGOTO(0x3E)\n";
			break;
		case INEQGOTO:
			output << "INEQGOTO(0x3F)\n";
			break;
		case LESSGOTO:
			output << "LESSGOTO(0x40)\n";
			break;
		case GRTRGOTO:
			output << "GRTRGOTO(0x41)\n";
			break;
		case GOTOASADDR:
			output << "GOTOASADDR(0x42)\n";
			break;
		case SYSCALL:
			output << "SYSCALL(0x43)\n";
			break;
		case SETERR:
			output << "SETERR(0x44)\n";
			break;
		case EXIT:
			output << "EXIT(0x45)\n";
			break;
		default:
			output << "UNKNOWN(0x" << std::hex << buff << std::dec << ")\n";
		}
	}
}

void Decompiler::open_and_run(std::string _input, std::string _output)
{
	open(_input, _output);
	run();
}

Decompiler::~Decompiler()
{
}
