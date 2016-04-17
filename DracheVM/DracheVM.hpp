#ifndef DRACHEVM_HPP
#define DRACHEVM_HPP

#include <iostream>
#include <fstream>
#include <stack>

#include "Object.hpp"
#include "Logger.hpp"

struct vm_state
{
	bool is_open = false;
	bool is_error_state = false;
	uint32_t current_position = 0x00000000;
};

class DracheVM
{
private:
	uint16_t address;		// The address before jump() was called. Used to restore control after loading in constants.
	Object _register[4] = {};
	std::stack<Object> stack;
	std::ifstream file;
	vm_state state;
	void vm_exit();
	void stack_dump();
public:
	DracheVM();
	DracheVM(const std::string filelocation);
	void open(std::string file);
	void run();
	Object &get_register(uint8_t register_index);
	std::stack<Object> &get_stack();
	int next();
	void rel_jump(int32_t jump_distance);
	void jump(int32_t jump_address = -1);
	void restore();
	vm_state get_state();
	DracheVM* get_vm();
	~DracheVM();
};

#endif
