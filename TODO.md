# TODO
Add the ability to pass multiple "executable" files to the VM.
Have the VM read the "header" of each file, if the header is ".dvmsrc" then compile, otherwise try and run and report errors.

Tweak how strings are handled internally, the current implementation is not ideal as each object on the stack will take up 512 bytes and strings can only be 511 characters long.(the rest of the space before 511 is wasted)
One idea for strings is to use new and delete(so this includes manual memory management).
Maybe include opcodes to allocate and deallocate C-strings.

# Testing
To emulate "stack frames" with function opcodes.

```
NEWFRAME 0x00 0x00
```

This opcode would create a new std::stack<Object> and increase an int that counts how many you have.
When you call
```
ENDFRAME
```
It deletes the stack and all of its contents