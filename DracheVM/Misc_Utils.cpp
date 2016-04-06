#include "Misc_Utils.hpp"


bool is_partial_string(std::string str)
{
	/*

		If the passed string starts with a quote but ends with a space, chances are it isn't a complete string;
		if that's the case, this function returns true, otherwise false.

	*/
	return false;
}

bool is_clean_string(std::string str)
{
	/*
	
		Partial or not, if the string contains escape characters or quotation marks other than the first and last - return false, otherwise return true.
		Escape characters need to be handled differently, hence this check.
	
	*/
	return false;
}

bool is_string(std::string str)
{
	/*
	
		If the passed string is properly quoted (and internal quotes were escaped) return true, else false.
	
	*/
	return false;
}