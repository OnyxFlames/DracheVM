#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <chrono>

#include "Decompiler.hpp"
#include "Compiler.hpp"
#include "DracheVM.hpp"
#include "Logger.hpp"
#include "SystemIO.hpp"
#include "RandomNumGen.hpp"

//#define NDEBUG
#include <cassert>


Logger logger("output.log");

bool time_performence = false;
bool decompile_mode = false;
bool compile_mode = false;
bool run_mode = false;
std::string compile_file;
std::string run_file;
std::string decompile_file_in, decompile_file_out;

std::chrono::time_point<std::chrono::system_clock> pre, post;

void print_help(std::string prog_name);

// I know, avoid globals at all costs, but it is global by design, 
// all parts of the vm need to access it and its much easier to make 
// it global than to pass it around to (almost) literally /every/ function that needs it.

SystemIO *io;
RandomNumGen *rng;

int main(int argc, char* argv[])
{
	// Assertions. If any of these fail, the VM isn't guaranteed to run properly.
	assert(sizeof(char)		== sizeof(int8_t));
	assert(sizeof(short)	== sizeof(int16_t));
	assert(sizeof(int)		== sizeof(int32_t));
	assert(sizeof(long long)== sizeof(int64_t));


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
		else if (std::strcmp(argv[i], "-r") == 0)
		{
			run_mode = true;
			run_file = argv[++i];
		}
		else if (std::strcmp(argv[i], "-c") == 0)
		{
			compile_mode = true;
			compile_file = argv[++i];
		}
		else if (std::strcmp(argv[i], "-d") == 0)
		{
			decompile_mode = true;
			decompile_file_in = argv[++i];
			decompile_file_out = argv[++i];
		}
		else if (std::strcmp(argv[i], "-time") == 0)
		{
			time_performence = true;
		}
	}
	Decompiler decompiler;
	Compiler compiler;
	DracheVM vm;

	vm.trace = true;

	std::shared_ptr<std::stack<Object>> stk_ptr = std::make_shared<std::stack<Object>>(vm.get_stack()); //	Get the pointer of the stack from the instance of the currently running VM. 
	io = new SystemIO(stk_ptr);																			//	This will be used by almost all the soon-to-be implemented static systems.
	rng = new RandomNumGen(stk_ptr);
	
	if (time_performence)
		pre = std::chrono::system_clock::now();

	if (decompile_mode)
		decompiler.open_and_run(decompile_file_in, decompile_file_out);

	if (compile_mode)
		compiler.open(compile_file);

	if (run_mode)
		vm.open(run_file);

	if (time_performence) 
	{
		post = std::chrono::system_clock::now();
		std::chrono::duration<long double> delta = (post - pre);
		std::cout << "\n\nEstimated run time: " << delta.count() << " seconds.\n";
	}
	return 0;
}

void print_help(std::string prog_name)
{
	std::cout << "Usage: \n\t" + prog_name +
		" -c <filename> to compile.\n\t" +
		prog_name + " -r <filename> to run.\n\t" +
		prog_name + " -time to time execution." << std::endl;
}
