#ifndef DRACHEVM_HPP
#define DRACHEVM_HPP

#include <iostream>
#include <fstream>
#include <stack>
#include <array>

#include "Object.hpp"
#include "Logger.hpp"
#include "Opcodes.hpp"

struct vm_state
{
	bool is_open = false;
	bool is_error_state = false;
	uint16_t error_flag;
	uint32_t current_position = 0x00000000;
};

class DracheVM
{
private:
	static constexpr uint32_t max_rom_size = _kilobyte;	// Max size(in bytes) that the VM can store in memory for the ROM.
	uint16_t index = 0x00;								// If the ROM is loaded into memory, this variable will be used, otherwise use the file streams pointer.
	bool in_memory = false;
	std::array<byte, max_rom_size> ROM{ NOP };			// If the physical ROM is max_rom_size bytes or less, load it into memory and read it off there.
	uint16_t address = 0x00;							// The address before jump() was called. Used to restore control after loading in constants.
	Object _register[4] = {};
	std::stack<Object> stack;
	std::ifstream file;
	vm_state state;
	void vm_exit();
	void stack_dump();
	size_t get_rom_size();
	void load_into_memory();
public:
	bool trace = false;

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
	vm_state& get_state();
	DracheVM* get_vm();
	~DracheVM();
};

#endif
