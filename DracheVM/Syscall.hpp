#ifndef SYSCALL_HPP
#define SYSCALL_HPP

#include "Opcodes.hpp"
#include "DracheVM.hpp"
#include <map>

#include "SystemIO.hpp"
#include "RandomNumGen.hpp"

const int IO = 0x01;
//const int _MODULE_ = 0x02; -- Cant remember what module I wanted to implement, but this code is reserved.
const int RANDNUMGEN = 0x03;

extern SystemIO *io;
extern RandomNumGen *rng;

void syscall(byte system, byte code, DracheVM &vm);

#endif
