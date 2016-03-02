#pragma once

typedef unsigned char byte;

enum Opcodes 
{
	NOP = 0x00,
	
	PUSH,	// Push takes the next byte as the numbers size as n, then pushes it onto the stack by reading the next n bytes.
	POP,	// Pop removes the top object off of the stack.

	ROT,	// Rot pops the first two objects into temporary buffers, then pushes the first, then second objects back onto the stack - swapping them.


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



			// Pop(n) pops the top of the stack onto the nth register. Cannot be manipulated this way - only overwritten.
	POP1, POP2, POP3, POP4,
			// Push(n) pushes the value in the register onto the top of the stack. Defaults to 0x00.
	PUSH1, PUSH2, PUSH3, PUSH4,

};

/*	
	--Variable Legend--
		1 = i8
		2 = i16
		3 = i32
		4 = i64
		5 = f32
		6 = f64
*/