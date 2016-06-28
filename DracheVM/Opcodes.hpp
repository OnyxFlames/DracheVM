#ifndef OPCODES_HPP
#define OPCODES_HPP

#include <cstdint>
#include <string>
#include <array>

typedef unsigned char byte;

constexpr uint8_t _byte = 1;
constexpr uint16_t _kilobyte = _byte * 1000;
constexpr uint32_t _megabyte = _kilobyte * 1000;
constexpr uint32_t _gigabyte = _megabyte * 1000;
//constexpr uint64_t _terabyte = _gigabyte * 1000;

enum Opcodes 
{
	NOP = 0x00,
	
	PUSH,	// Push takes the next byte as the numbers size as n, then pushes it onto the stack by reading the next n bytes.
	POP,	// Pop removes the top object off of the stack.
	ALLOC,	// This opcode allocates heap memory by the byte up to 2^16 bytes at a time.
	DEALLOC,// Deallocates heap memory by 2^16 bytes at a time.
	ROT,	// Rot pops the first two objects into temporary buffers, then pushes the first, then second objects back onto the stack - swapping them.
	MOV,	// Replaces POPN/PUSHN functions. Moves from stack to register or register to stack. Syntax: MOV 0x00 0x01 moves stack contents to register 1.

			// These opcodes manipulate n amount of bits of the objects in the stack, pushing the result(s) onto the stack.
	ADD8, SUB8, MUL8, DIV8,
	ADD16, SUB16, MUL16, DIV16,
	ADD32, SUB32, MUL32, DIV32,
	ADD64, SUB64, MUL64, DIV64,
	ADDF32, SUBF32, MULF32, DIVF32,
	ADDF64, SUBF64, MULF64, DIVF64,


			// Variable type conversion opcodes.
	i8TOi16, i8TOi32, i8TOi64, i8TOf32, i8TOf64,
	i16TOi8, i16TOi32, i16TOi64, i16TOf32, i16TOf64,
	i32TOi8, i32TOi16, i32TOi64, i32TOf32, i32TOf64,
	i64TOi8, i64TOi16, i64TOi32, i64TOf32, i64TOf64,
	f32TOi8, f32TOi16, f32TOi32, f32TOi64, f32TOf64,
	f64TOi8, f64TOi16, f64TOi32, f64TOi64, f64TOf32,

	GOTO,
			// Conditional operators. In order: If equal, if not equal, if less than, if greater than.
	EQGOTO,
	INEQGOTO,
	LESSGOTO,
	GRTRGOTO,

			/*
				DVM Example:
				LESSGOTO 0x00 0x00
				
				C example:
				if(top < bottom)
				{
					goto 0x0000;
				}
			*/

			// Pop the top value of the stack and treat it like an address for goto.
			// This opcode is for when the data in the rom exceeds (2^16) - 32 bytes, or 65,504 bytes(65.5 Kb)
	GOTOASADDR,

	SYSCALL,

	SETERR,

	EXIT,




	_LAST_OP,
	TOTAL_OPCODES = _LAST_OP
};

/*	
	--Variable Legend--
		1 = char*
		2 = i8
		3 = i16
		4 = i32
		5 = i64
		6 = f32
		7 = f64
*/

static std::array<std::string, TOTAL_OPCODES> opcode_strs =
{
	"NOP", "PUSH", "POP", "ALLOC", "DEALLOC", "ROT", "MOV",

	"ADD8", "SUB8", "MUL8", "DIV8",
	"ADD16", "SUB16", "MUL16", "DIV16",
	"ADD32", "SUB32", "MUL32", "DIV32",
	"ADD64", "SUB64", "MUL64", "DIV64",
	"ADDF32","SUBF32", "MULF32", "DIVF32",
	"ADDF64", "SUBF64", "MULF64", "DIVF64",

	"i8TOi16", "i8TOi32", "i8TOi64", "i8TOf32", "i8TOf64",
	"i16TOi8", "i16TOi32", "i16TOi64", "i16TOf32", "i16TOf64",
	"i32TOi8", "i32TOi16", "i32TOi64", "i32TOf32", "i32TOf64",
	"i64TOi8", "i64TOi16", "i64TOi32", "i64TOf32", "i64TOf64",
	"f32TOi8", "f32TOi16", "f32TOi32", "f32TOi64", "f32TOf64",
	"f64TOi8", "f64TOi16", "f64TOi32", "f64TOi64", "f64TOf32",

	"GOTO", "EQGOTO", "INEQGOTO", "LESSGOTO", "GRTRGOTO", "GOTOASADDR", "SYSCALL", "SETERR", "EXIT",

};

#endif