debug:
	g++ DracheVM/main.cpp DracheVM/Compiler.cpp DracheVM/DracheVM.cpp DracheVM/Logger.cpp DracheVM/Misc_Utils.cpp DracheVM/Opcodes.hpp DracheVM/RandomNumGen.cpp DracheVM/StackManagement.cpp DracheVM/Syscall.cpp DracheVM/SystemIO.cpp DracheVM/VariableManip.cpp -Wall -pedantic -std=c++11 -o Debug/DracheVM-Debug
release:
	g++ DracheVM/main.cpp DracheVM/Compiler.cpp DracheVM/DracheVM.cpp DracheVM/Logger.cpp DracheVM/Misc_Utils.cpp DracheVM/Opcodes.hpp DracheVM/RandomNumGen.cpp DracheVM/StackManagement.cpp DracheVM/Syscall.cpp DracheVM/SystemIO.cpp DracheVM/VariableManip.cpp -std=c++11 -o Release/DracheVM-Release
