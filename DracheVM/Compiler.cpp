#include "Compiler.hpp"
#include "Misc_Utils.hpp"	// is_string(std::string) && is_partial_string(std::string)

#include "SystemIO.hpp"

#include <map>

Compiler::Compiler() {}

Compiler::Compiler(const std::string &file)
{
	open(file);
}

void Compiler::open(const std::string &file)
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
	std::map<std::string, int16_t> label_map;
	int16_t position_count = -1;
	while (!source_file.eof())
	{
		source_file >> buffer;
		position_count++;

		// If the first two digits are '0' and 'x' then its a hex number.
		if (buffer[0] == '0' && buffer[1] == 'x') bytecode.push_back(std::stoi(buffer, 0, 16));
		else if (isdigit(buffer[0]))
		{
			// If the character starts as a number but the second number isnt a 'x' (so it isnt a byte literal)
			for (char c : buffer)
				bytecode.push_back(c);
			bytecode.push_back(0x00);
		}
		else if (buffer[0] == '.') // label creation.
		{
				buffer.erase(buffer.begin());	// remove the '.' and store the label and its position in a map to be looked up later.
				label_map.insert(std::pair<std::string, int16_t>(buffer, position_count));
		}
		else if (buffer[0] == '\"')
		{
			if (is_string(buffer))
			{
				if (is_clean_string(buffer))
				{
					for (char c : buffer) 
					{
						if (c == '"')
							break;
						bytecode.push_back(c);
					}
					bytecode.push_back(0x00);
					//If it's a proper, clean string, just dump all of it's data into the bytecode omitting the quotation marks.
				}
			}
			else if (is_partial_string(buffer))
			{

			}
		}
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
		else if (buffer == "ADD8") bytecode.push_back(ADD8);
		else if (buffer == "SUB8") bytecode.push_back(SUB8);
		else if (buffer == "MUL8") bytecode.push_back(MUL8);
		else if (buffer == "DIV8") bytecode.push_back(DIV8);
		else if (buffer == "ADD16") bytecode.push_back(ADD16);
		else if (buffer == "SUB16") bytecode.push_back(SUB16);
		else if (buffer == "MUL16") bytecode.push_back(MUL16);
		else if (buffer == "DIV16") bytecode.push_back(DIV16);
		else if (buffer == "ADD32") bytecode.push_back(ADD32);
		else if (buffer == "SUB32") bytecode.push_back(SUB32);
		else if (buffer == "MUL32") bytecode.push_back(MUL32);
		else if (buffer == "DIV32") bytecode.push_back(DIV32);
		else if (buffer == "ADD64") bytecode.push_back(ADD64);
		else if (buffer == "SUB64") bytecode.push_back(SUB64);
		else if (buffer == "MUL64") bytecode.push_back(MUL64);
		else if (buffer == "DIV64") bytecode.push_back(DIV64);
		else if (buffer == "ADDF32") bytecode.push_back(ADDF32);
		else if (buffer == "SUBF32") bytecode.push_back(SUBF32);
		else if (buffer == "MULF32") bytecode.push_back(MULF32);
		else if (buffer == "DIVF32") bytecode.push_back(DIVF32);
		else if (buffer == "ADDF64") bytecode.push_back(ADDF64);
		else if (buffer == "SUBF64") bytecode.push_back(SUBF64);
		else if (buffer == "MULF64") bytecode.push_back(MULF64);
		else if (buffer == "DIVF64") bytecode.push_back(DIVF64);
		else if (buffer == "SYSCALL") bytecode.push_back(SYSCALL);
		else if (buffer == "GOTO") bytecode.push_back(GOTO);
		else if (buffer == "EQGOTO") bytecode.push_back(EQGOTO);
		else if (buffer == "IO_PRINTNL") bytecode.push_back(PRINTNL);
		else if (buffer == "IO_PRINTSTR") bytecode.push_back(PRINTSTR);
		else if (buffer == "IO_PRINTCHR") bytecode.push_back(PRINTCHR);
		else if (buffer == "IO_PRINTINT8") bytecode.push_back(PRINTINT8);
		else if (buffer == "IO_PRINTINT16") bytecode.push_back(PRINTINT16);
		else if (buffer == "IO_PRINTINT32") bytecode.push_back(PRINTINT32);
		else if (buffer == "IO_PRINTINT64") bytecode.push_back(PRINTINT64);
		else if (buffer == "IO_PRINTF32") bytecode.push_back(PRINTF32);
		else if (buffer == "IO_PRINTF64") bytecode.push_back(PRINTF64);
		else if (buffer == "IO_READSTR") bytecode.push_back(READSTR);
		else if (buffer == "IO_READCHR") bytecode.push_back(READCHR);
		else if (buffer == "IO_READINT8") bytecode.push_back(READINT8);
		else if (buffer == "IO_READINT16") bytecode.push_back(READINT16);
		else if (buffer == "IO_READINT32") bytecode.push_back(READINT32);
		else if (buffer == "IO_READINT64") bytecode.push_back(READINT64);
		else if (buffer == "EXIT")	bytecode.push_back(EXIT);
		else if (is_declared(label_map, buffer))
		{
			// If the location of the referenced label is greater than 255, we'll need two bytes to refer to it.
			// The to_bytes(int16_t val); function returns an array of two bytes that will get emitted into the rom's bytecode.
			if (label_map[buffer] > 255)
			{
				// This pushes back the byte value returned from to_bytes when passed the value of the label's position, in index 0, or 1.
				bytecode.push_back
					(to_bytes(label_map[buffer])[0]);
				bytecode.push_back
					(to_bytes(label_map[buffer])[1]);
			}
			// If the location of the referenced label is smaller than 255, we still have to emit two bytes.
			// The first byte is just going to be 0x00, as we only need the second one to refer to the location.
			else
			{
				bytecode.push_back(0x00);
				bytecode.push_back((int8_t)label_map[buffer]);
			}
		}
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
