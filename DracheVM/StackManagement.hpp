#pragma once

#include <stack>
#include <fstream>

#include "Object.hpp"
#include "DracheVM.hpp"

void push_to_stack(std::ifstream &file, std::stack<Object> &stack);

void pop_to_register(uint8_t register_index, DracheVM &vm);

void push_from_register(uint8_t register_index, DracheVM &vm);