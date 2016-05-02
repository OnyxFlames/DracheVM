#ifndef OPCODES_HPP
#define OPCODES_HPP

typedef unsigned char byte;

enum Opcodes 
{
	NOP = 0x00,
	
	PUSH,	// Push takes the next byte as the numbers size as n, then pushes it onto the stack by reading the next n bytes.
	POP,	// Pop removes the top object off of the stack.
	DEALLOC,// Deallocated the top value on the stack. The typically is called right before the value is popped off the stack.
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
	/* TODO: Remove these opcodes once it no longer breaks the build.
			// Pop(n) pops the top of the stack onto the nth register. Cannot be manipulated this way - only overwritten.
	// POP1, POP2, POP3, POP4,
			// Push(n) pushes the value in the register onto the top of the stack. Defaults to 0x00.
	// PUSH1, PUSH2, PUSH3, PUSH4,
	*/

	SYSCALL,


	EXIT,
};

#endif

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
