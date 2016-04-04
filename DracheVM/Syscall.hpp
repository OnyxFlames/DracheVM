#pragma once

#include "Opcodes.hpp"
#include "DracheVM.hpp"
#include <map>

#include "SystemIO.hpp"

const int IO = 0x01;
const int _MODULE_ = 0x02;		// Cant remember what module I wanted to implement.
const int RANDNUMGEN = 0x03;

extern SystemIO *io;

void syscall(byte system, byte code, DracheVM &vm);