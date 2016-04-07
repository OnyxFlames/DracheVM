#include "Misc_Utils.hpp"

#include <cctype>

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