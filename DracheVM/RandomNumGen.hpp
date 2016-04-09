#pragma once

#include <memory>
#include <stack>
#include <cstdlib>
#include <cstdint>

#include "Object.hpp"
#include "Opcodes.hpp"
#include "DracheVM.hpp"
#include "Logger.hpp"

extern Logger logger;


enum RNG_OPCODES 
{
	SETSEED,			// set the seed for the random number generator.
	GENERATE,			// generate a random number using MIN and MAX as its range.
	GENERATE_WITHIN,	// generate a random number using the top of the stack as a min, and the second to the top as the max.
	SETMIN,				// set a new min result.
	SETMAX,				// set a new max result.
};

class RandomNumGen
{
private:

	int32_t _seed = 0;
	double _min = 0.0, _max = 1.0;

	bool init = false;
	std::shared_ptr<std::stack<Object>> stack_ptr;
	double generate(double min, double max);
public:
	RandomNumGen();
	RandomNumGen(std::shared_ptr<std::stack<Object>> &_stack_ptr);
	bool RandomNumGen::bind_stack(std::shared_ptr<std::stack<Object>> &_stack_ptr);
	void run_opcode(byte opcode, DracheVM &vm);
	~RandomNumGen();
};

