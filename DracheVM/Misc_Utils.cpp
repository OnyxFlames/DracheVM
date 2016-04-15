#include "Misc_Utils.hpp"

#include <cctype>

void clear_registers(Object _registers[4])
{
	for (int i = 0; i < 3; i++)
	{
		_registers[i].i64 = 0x00;
	}
}

bool is_partial_string(std::string str)
{
	if (str.at(str.size()) == '"')
		return false;
	return true;
}

bool is_clean_string(std::string str)
{
	for (char c : str)
	{
		if (isspace(c) ||
			ispunct(c) ||
			iscntrl(c))
			return false;
	}
	return true;
}

bool is_string(std::string str)
{
	if (str.at(0x00) == '"' && str.at(str.size()) == '"')
		return true;
	else
		return false;
}

bool is_declared(std::map<std::string, int16_t> &_label_map, std::string _label)
{
	// iterate through the map checking for the label.
	for (std::pair<std::string, int> pair : _label_map) 
	{
		if (pair.first == _label)
			return true;
		else
			continue;
	}
	return false;
}

uint16_t assemble_16bit_address(uint8_t first, uint8_t second)
{
	uint16_t ret = first;
	ret <<= 8;
	ret += second;
	return ret;
}

std::array<int8_t, 2> to_bytes(int16_t val)
{
	int8_t buff[2] = { 0 };		// Create a two byte buffer.
	buff[1] = (int8_t)val;		// Store the last 8 bits into the second byte.
	val >>= 8;					// Slide the first 8 bits over into the last 8.
	buff[0] = (int8_t)val;		// Store the (now) last 8 bits into the first byte.
	return std::array<int8_t, 2>{ buff[0], buff[1] };
}