#ifndef DECOMPILER_HPP
#define DECOMPILER_HPP

#include "Opcodes.hpp"
#include "Object.hpp"

#include <iostream>
#include <fstream>
#include <string>

/*

	Debugging decompiler.
	This class will take a compiled dvm file and output known opcodes and their byte value into a textfile to aid debugging.
	Eg. 0x01 0x00 0x00 -> PUSH(0x01) NOP(0x00) NOP(0x00)
	If the opcode is not known, the decompiler will just output the byte in parenthesis.

*/

class Decompiler
{
	std::ifstream input;
	std::ofstream output;
public:
	Decompiler();
	Decompiler(std::string _input, std::string _output);
	void open(std::string _input, std::string _output);
	void run();
	void open_and_run(std::string _input, std::string _output);
	~Decompiler();
};

#endif