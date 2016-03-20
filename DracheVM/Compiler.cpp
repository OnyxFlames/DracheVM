#include "Compiler.hpp"

Compiler::Compiler() {}

Compiler::Compiler(std::string file)
{
	open(file);
}

void Compiler::open(std::string file)
{
	file_name = file;
	source_file.open(file);
	if (!source_file.is_open())
	{
		std::cerr << "compile error: unable to open source file: " << file_name << std::endl;
		std::exit(-1);
	}
	run();
}

void Compiler::run()
{
	std::string buffer = "";
	while (!source_file.eof())
	{
		source_file >> buffer;

		// If the first two digits are '0' and 'x' then its a hex number.
		if (buffer[0] == '0' && buffer[1] == 'x') bytecode.push_back(std::stoi(buffer, 0, 16));
		else if (buffer == "PUSH") bytecode.push_back(PUSH);
		else if (buffer == "POP")  bytecode.push_back(POP);
		else if (buffer == "ROT")  bytecode.push_back(ROT);
		else if (buffer == "POP1") bytecode.push_back(POP1);
		else if (buffer == "POP2") bytecode.push_back(POP2);
		else if (buffer == "POP3") bytecode.push_back(POP3);
		else if (buffer == "POP4") bytecode.push_back(POP4);
		else if (buffer == "PUSH1") bytecode.push_back(PUSH1);
		else if (buffer == "PUSH2") bytecode.push_back(PUSH2);
		else if (buffer == "PUSH3") bytecode.push_back(PUSH3);
		else if (buffer == "PUSH4") bytecode.push_back(PUSH4);
		else if (buffer == "EXIT")	bytecode.push_back(EXIT);
	}

	gen();
}
void Compiler::gen()
{
	output_file.open(file_name + ".dvm", std::ios::binary);
	if (!output_file.is_open())
	{
		std::cerr << "compile error: unable to create file: " << (file_name + ".dvm") << std::endl;
		std::exit(-1);
	}

	for (byte c : bytecode)
	{
		output_file << c;
	}
}

Compiler::~Compiler()
{
}
