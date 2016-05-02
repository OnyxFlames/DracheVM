#ifndef VARIABLEMANIP_HPP
#define VARIABLEMANIP_HPP

#include "DracheVM.hpp"

// i8

void variable_handler(byte value, DracheVM &vm);

void add8(DracheVM &vm);
void sub8(DracheVM &vm);
void mul8(DracheVM &vm);
void div8(DracheVM &vm);

void add16(DracheVM &vm);
void sub16(DracheVM &vm);
void mul16(DracheVM &vm);
void div16(DracheVM &vm);

void add32(DracheVM &vm);
void sub32(DracheVM &vm);
void mul32(DracheVM &vm);
void div32(DracheVM &vm);

void add64(DracheVM &vm);
void sub64(DracheVM &vm);
void mul64(DracheVM &vm);
void div64(DracheVM &vm);

void addf32(DracheVM &vm);
void subf32(DracheVM &vm);
void mulf32(DracheVM &vm);
void divf32(DracheVM &vm);

void addf64(DracheVM &vm);
void subf64(DracheVM &vm);
void mulf64(DracheVM &vm);
void divf64(DracheVM &vm);

#endif
