#pragma once

#include <string>
#include <map>

bool is_partial_string(std::string str);

bool is_clean_string(std::string str);

bool is_string(std::string str);

bool is_declared(std::map<std::string, int> &_label_map, std::string _label);