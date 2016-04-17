#ifndef MISC_UTILS_HPP
#define MISC_UTILS_HPP

#include <cstdlib>
#include <string>
#include <map>
#include <array>

#include "Object.hpp"

void clear_registers(Object _registers[4]);

bool is_partial_string(std::string str);

bool is_clean_string(std::string str);

bool is_string(std::string str);

bool is_declared(std::map<std::string, int16_t> &_label_map, std::string _label);

uint16_t assemble_16bit_address(uint8_t first, uint8_t second);

std::array<int8_t, 2> to_bytes(int16_t val);

#endif
