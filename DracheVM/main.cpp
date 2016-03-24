#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

#include "Compiler.hpp"
#include "DracheVM.hpp"
#include "Logger.hpp"

Logger logger("output.log");

bool compile_mode = false;
bool run_mode = false;
std::string compile_file;
std::string run_file;

void print_help(std::string prog_name);

int main(int argc, char* argv[])
{

	if (argc < 2)
	{
		std::cerr << argv[0] << ": no arguments passed. Exiting." << std::endl;
		return -1;
	}
	for (int i = 1; i < argc; i++)
	{
		if (std::strcmp(argv[i], "-help") == 0)
		{
			print_help(argv[0]);
			std::exit(1);
		}
		if (std::strcmp(argv[i], "-r") == 0)
		{
			run_mode = true;
			run_file = argv[++i];
		}
		if (std::strcmp(argv[i], "-c") == 0)
		{
			compile_mode = true;
			compile_file = argv[++i];
		}
	}

	Compiler compiler;
	DracheVM vm;

	if (compile_mode)
		compiler.open(compile_file);
	if (run_mode)
		vm.open(run_file);

	return 0;
}

void print_help(std::string prog_name)
{
	std::cout << "Usage: \n\t" + prog_name +
		" -c <filename> to compile.\n\t" +
		prog_name + " -r <filename> to run." << std::endl;
}