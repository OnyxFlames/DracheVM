#How bytecode is read.
Bytecode is contextual in the DVM.
By that, I mean that after reading a byte, that byte and the context around that byte dictated how many more bytes the DVM is going to read and process.
For example:
```
PUSH 0x01 0xff
```
Push causes the DVM to read the next byte, and depending on that bytes value, it will read either 1, 2, 4, or 8 bytes afterward.(8, 16, 32, and 64 bits respectively).
The legend for what value dictates how many bytes are read and be found as a comment in [Opcodes.hpp](/DracheVM/Opcodes.hpp)
Other opcodes do not read any bytes passed the originial one and jump straight back to executing code after.
```
ROT
```
For example, ROT just rotates the top two values in a stack, nothing else. Therefore it doesn't need any more information.
If ROT was to fail, it would write to the error log which defaults to Output.log.