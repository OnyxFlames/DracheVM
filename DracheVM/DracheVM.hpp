#pragma once

#include <iostream>
#include <fstream>
#include <stack>

#include "Object.hpp"
#include "Logger.hpp"

class DracheVM
{
private:
	Object _register[4] = { 0x00 };
	std::stack<Object> stack;
	std::ifstream file;
public:
	DracheVM(const std::string filelocation);
	void run();
	Object &get_register(uint8_t register_index);
	std::stack<Object> &get_stack();
	~DracheVM();
};

