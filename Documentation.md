#How bytecode is read.
Bytecode is contextual in the DVM.
By that, I mean that after reading a byte, that byte and the context around that byte dictated how many more bytes the DVM is going to read and process.
For example:
```
PUSH 0x01 0xff
```
The PUSH opcode reads the next two bytes as a 16-bit wide address, jumps to that location in the ROM and reads the byte at that location.
The value of that byte determines how many following bytes the VM will read.
0x01 - reads every following byte until a NULL byte is read(0x00).
0x02 - reads one byte, this is often used for loading single characters into memory.
0x03 - reads two bytes, used for loading short's into memory. Can be used along side GOTOASADDR to jump to locations in the ROM from values in the memory.
0x04 - reads four bytes, commonly used for loading 32 bit integers into memory.
0x05 - reads 8 bytes, used for loading 64-bit values into memory. Can also be used with GOTOASADDR to get up to ((2^64)/2) - 1 addresses in memory. (The reason for that being the max value will be mentioned later on)
0x06 - This byte is used for loading 32-bit wide floating point numbers. It is not yet support by the VM.
0x07 - This byte is used for loading 64-bit wide(double) floating point numbers. It is not yet support by the VM.
0x08 - 0xff - These bytes will cause the vm to throw an error and exit due to it not knowing how to handle these values, it asssumes that the ROM is corrupted and could cause harm if kept running.
```
POP
```
This opcode will pop the top value off of the stack.
NOTE: if the value has been manually allocated internally by the compiler(C-string literals) it most likely will not deallocate it before popping, causing a memory leak.
```
DEALLOC
```
This opcode will attempt to deallocate the value pointed to by the top value of the stack(C-string literal)
If this fails, or is called when the top of the stack is not manually allocated, this can cause a crash.

NOTE: You can give the top value any value you want and attempt to deallocate it using this opcode, if the value was manually allocated at some point, this will work. Although it is not advised.
```
ROT
```
For example, ROT just rotates the top two values in a stack, nothing else. Therefore it doesn't need any more information.
If ROT was to fail, it would write to the error log which defaults to Output.log.
```
ADD8, SUB8, MUL8, DIV8,
ADD16, SUB16, MUL16, DIV16,
ADD32, SUB32, MUL32, DIV32,
ADD64, SUB64, MUL64, DIV64,
ADDF32, SUBF32, MULF32, DIVF32,
ADDF64, SUBF64, MULF64, DIVF64
```
The above opcodes operate one the variables on the stack. Adding, multiplying, dividing, and subtracting the values assuming they are of the same size.
```
i8TOi16, i8TOi32, i8TOi64, i8TOf32, i8TOf64,
i16TOi8, i16TOi32, i16TOi64, i16TOf32, i16TOf64,
i32TOi8, i32TOi16, i32TOi64, i32TOf32, i32TOf64,
i64TOi8, i64TOi16, i64TOi32, i64TOf32, i64TOf64,
f32TOi8, f32TOi16, f32TOi32, f32TOi64, f32TOf64,
f64TOi8, f64TOi16, f64TOi32, f64TOi64, f64TOf32,
```
These above opcodes convert the top value from one type to another.
Ex. i8TOi16 will load the top value of the stack as an 8 bit wide integer and cast it into a 16-bit wide integer and push it back onto the stack.
If this is done properly, the values should remain unchanged, only their min/max size capability should be altered.
```
EQGOTO,
INEQGOTO,
LESSGOTO,
GRTRGOTO,
```
These opcodes are the conditional operators.
The compare the top two values of the stack for either equality, inequality, the first being less than the second, or the first being greater than the second.
If the call is successful, the vm will jump to the following 16-bit address and continue execution. Otherwise it will skip the next two bytes(the address) and continue executing normally.
These comparisons are very literal comparisons when it comes to all values except floating point. For equality/inequality it will temporarily round the value before comparing to assure accuracy.