#ifndef STACKMANAGEMENT_HPP
#define STACKMANAGEMENT_HPP

#include <stack>
#include <fstream>

#include "Object.hpp"
#include "DracheVM.hpp"
#include "Misc_Utils.hpp"

void push_to_stack(DracheVM &vm);

void pop_to_register(uint8_t register_index, DracheVM &vm);

void push_from_register(uint8_t register_index, DracheVM &vm);

#endif
