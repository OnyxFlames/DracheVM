#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "Opcodes.hpp"

/*
	Mnemonic bytecode compiler (1-1 translation)

*/

class Compiler
{
private:
	std::string file_name;
	std::ifstream source_file;
	std::ofstream output_file;
	std::vector<byte> bytecode;
public:
	Compiler();
	Compiler(const std::string &file);
	void open(const std::string &file);
	void run();
	void gen();
	~Compiler();
};

