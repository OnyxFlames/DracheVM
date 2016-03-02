#include <iostream>
#include <fstream>

#include "DracheVM.hpp"
#include "Logger.hpp"

Logger logger("output.log");

int main(int argc, char* argv[])
{
	logger.log("Starting VM.");
	DracheVM vm("Test.dvm");

	return 0;
}