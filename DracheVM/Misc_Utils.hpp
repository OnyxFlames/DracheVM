#ifndef MISC_UTILS_HPP
#define MISC_UTILS_HPP

#include <cstdlib>
#include <string>
#include <map>
#include <array>
#include <vector>

#include "DracheVM.hpp"
#include "Object.hpp"
#include "Opcodes.hpp"


void clear_registers(Object _registers[4]);

bool is_partial_string(std::string str);

bool is_clean_string(std::string str);

bool is_string(std::string str);

bool is_declared(std::map<std::string, int16_t> &_label_map, std::string _label);

bool is_in_range(int64_t min, int64_t max, int64_t val);

std::string from_c_str(DracheVM &vm);

uint16_t assemble_16bit_address(uint8_t first, uint8_t second);

std::array<int8_t, 2> to_bytes(int16_t val);

#endif
