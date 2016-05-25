#include "VariableManip.hpp"
#include "Logger.hpp"

#include <cstdlib>

extern Logger logger;

Object object_buffer;

void variable_handler(byte value, DracheVM &vm)
{
	switch (value)
	{
	case ADD8:
		add8(vm);
		break;
	case SUB8:
		sub8(vm);
		break;
	case MUL8:
		mul8(vm);
		break;
	case DIV8:
		div8(vm);
		break;
	case ADD16:
		add16(vm);
		break;
	case SUB16:
		sub16(vm);
		break;
	case MUL16:
		mul16(vm);
		break;
	case DIV16:
		div16(vm);
		break;
	case ADD32:
		add32(vm);
		break;
	case SUB32:
		sub32(vm);
		break;
	case MUL32:
		mul32(vm);
		break;
	case DIV32:
		div32(vm);
		break;
	case ADD64:
		add64(vm);
		break;
	case SUB64:
		sub64(vm);
		break;
	case MUL64:
		mul64(vm);
		break;
	case DIV64:
		div64(vm);
		break;
	case ADDF32:
		addf32(vm);
		break;
	case SUBF32:
		subf32(vm);
		break;
	case MULF32:
		mulf32(vm);
		break;
	case DIVF32:
		divf32(vm);
		break;
	case ADDF64:
		addf64(vm);
		break;
	case SUBF64:
		subf64(vm);
		break;
	case MULF64:
		mulf64(vm);
		break;
	case DIVF64:
		divf64(vm);
		break;
	}
}

void add8(DracheVM &vm)
{
	if (vm.get_stack().size() < 2)
	{
		logger.elog("vm error: attempted to pop from an empty stack! Exiting. (OPCODE ADD8)");
		std::exit(-1);
	}
	int8_t buff[2] = { 0x00 };
	buff[0] = vm.get_stack().top().get_i8();
	vm.get_stack().pop();
	buff[1] = vm.get_stack().top().get_i8();
	vm.get_stack().pop();
	object_buffer.set_i8((buff[0] + buff[1]));
	vm.get_stack().push(object_buffer);
}
void sub8(DracheVM &vm)
{
	if (vm.get_stack().size() < 2)
	{
		logger.elog("vm error: attempted to pop from an empty stack! Exiting. (OPCODE SUB8)");
		std::exit(-1);
	}
	int8_t buff[2] = { 0x00 };
	buff[0] = vm.get_stack().top().get_i8();
	vm.get_stack().pop();
	buff[1] = vm.get_stack().top().get_i8();
	vm.get_stack().pop();
	object_buffer.set_i8((buff[0] - buff[1]));
	vm.get_stack().push(object_buffer);
}
void mul8(DracheVM &vm)
{
	if (vm.get_stack().size() < 2)
	{
		logger.elog("vm error: attempted to pop from an empty stack! Exiting. (OPCODE MUL8)");
		std::exit(-1);
	}
	int8_t buff[2] = { 0x00 };
	buff[0] = vm.get_stack().top().get_i8();
	vm.get_stack().pop();
	buff[1] = vm.get_stack().top().get_i8();
	vm.get_stack().pop();
	object_buffer.set_i8((buff[0] * buff[1]));
	vm.get_stack().push(object_buffer);
}
void div8(DracheVM &vm)
{
	if (vm.get_stack().size() < 2)
	{
		logger.elog("vm error: attempted to pop from an empty stack! Exiting. (OPCODE DIV8)");
		std::exit(-1);
	}
	int8_t buff[2] = { 0x00 };
	buff[0] = vm.get_stack().top().get_i8();
	vm.get_stack().pop();
	buff[1] = vm.get_stack().top().get_i8();
	vm.get_stack().pop();
	object_buffer.set_i8((buff[0] / buff[1]));
	vm.get_stack().push(object_buffer);
}

void add16(DracheVM &vm)
{
	if (vm.get_stack().size() < 2)
	{
		logger.elog("vm error: attempted to pop from an empty stack! Exiting. (OPCODE ADD16)");
		std::exit(-1);
	}
	int16_t buff[2] = { 0x00 };
	buff[0] = vm.get_stack().top().get_i16();
	vm.get_stack().pop();
	buff[1] = vm.get_stack().top().get_i16();
	vm.get_stack().pop();
	object_buffer.set_i16((buff[0] + buff[1]));
	vm.get_stack().push(object_buffer);
}
void sub16(DracheVM &vm)
{
	if (vm.get_stack().size() < 2)
	{
		logger.elog("vm error: attempted to pop from an empty stack! Exiting. (OPCODE SUB16");
		std::exit(-1);
	}
	int16_t buff[2] = { 0x00 };
	buff[0] = vm.get_stack().top().get_i16();
	vm.get_stack().pop();
	buff[1] = vm.get_stack().top().get_i16();
	vm.get_stack().pop();
	object_buffer.set_i16((buff[0] - buff[1]));
	vm.get_stack().push(object_buffer);
}
void mul16(DracheVM &vm)
{
	if (vm.get_stack().size() < 2)
	{
		logger.elog("vm error: attempted to pop from an empty stack! Exiting. (OPCODE MUL16)");
		std::exit(-1);
	}
	int16_t buff[2] = { 0x00 };
	buff[0] = vm.get_stack().top().get_i16();
	vm.get_stack().pop();
	buff[1] = vm.get_stack().top().get_i16();
	vm.get_stack().pop();
	object_buffer.set_i16((buff[0] * buff[1]));
	vm.get_stack().push(object_buffer);
}
void div16(DracheVM &vm)
{
	if (vm.get_stack().size() < 2)
	{
		logger.elog("vm error: attempted to pop from an empty stack! Exiting. (OPCODE DIV16)");
		std::exit(-1);
	}
	int16_t buff[2] = { 0x00 };
	buff[0] = vm.get_stack().top().get_i16();
	vm.get_stack().pop();
	buff[1] = vm.get_stack().top().get_i16();
	vm.get_stack().pop();
	object_buffer.set_i16((buff[0] / buff[1]));
	vm.get_stack().push(object_buffer);
}

void add32(DracheVM &vm)
{
	if (vm.get_stack().size() < 2)
	{
		logger.elog("vm error: attempted to pop from an empty stack! Exiting. (OPCODE ADD32)");
		std::exit(-1);
	}
	int32_t buff[2] = { 0x00 };
	buff[0] = vm.get_stack().top().get_i32();
	vm.get_stack().pop();
	buff[1] = vm.get_stack().top().get_i32();
	vm.get_stack().pop();
	object_buffer.set_i32((buff[0] + buff[1]));
	vm.get_stack().push(object_buffer);
}
void sub32(DracheVM &vm)
{
	if (vm.get_stack().size() < 2)
	{
		logger.elog("vm error: attempted to pop from an empty stack! Exiting. (OPCODE SUB32)");
		std::exit(-1);
	}
	int32_t buff[2] = { 0x00 };
	buff[0] = vm.get_stack().top().get_i32();
	vm.get_stack().pop();
	buff[1] = vm.get_stack().top().get_i32();
	vm.get_stack().pop();
	object_buffer.set_i32((buff[0] - buff[1]));
	vm.get_stack().push(object_buffer);
}
void mul32(DracheVM &vm)
{
	if (vm.get_stack().size() < 2)
	{
		logger.elog("vm error: attempted to pop from an empty stack! Exiting. (OPCODE MUL32)");
		std::exit(-1);
	}
	int32_t buff[2] = { 0x00 };
	buff[0] = vm.get_stack().top().get_i32();
	vm.get_stack().pop();
	buff[1] = vm.get_stack().top().get_i32();
	vm.get_stack().pop();
	object_buffer.set_i32((buff[0] * buff[1]));
	vm.get_stack().push(object_buffer);
}
void div32(DracheVM &vm)
{
	if (vm.get_stack().size() < 2)
	{
		logger.elog("vm error: attempted to pop from an empty stack! Exiting. (OPCODE DIV32)");
		std::exit(-1);
	}
	int32_t buff[2] = { 0x00 };
	buff[0] = vm.get_stack().top().get_i32();
	vm.get_stack().pop();
	buff[1] = vm.get_stack().top().get_i32();
	vm.get_stack().pop();
	object_buffer.set_i32((buff[0] / buff[1]));
	vm.get_stack().push(object_buffer);
}

void add64(DracheVM &vm)
{
	if (vm.get_stack().size() < 2)
	{
		logger.elog("vm error: attempted to pop from an empty stack! Exiting. (OPCODE ADD64)");
		std::exit(-1);
	}
	int64_t buff[2] = { 0x00 };
	buff[0] = vm.get_stack().top().get_i64();
	vm.get_stack().pop();
	buff[1] = vm.get_stack().top().get_i64();
	vm.get_stack().pop();
	object_buffer.set_i64((buff[0] + buff[1]));
	vm.get_stack().push(object_buffer);
}
void sub64(DracheVM &vm)
{
	if (vm.get_stack().size() < 2)
	{
		logger.elog("vm error: attempted to pop from an empty stack! Exiting. (OPCODE SUB64)");
		std::exit(-1);
	}
	int64_t buff[2] = { 0x00 };
	buff[0] = vm.get_stack().top().get_i64();
	vm.get_stack().pop();
	buff[1] = vm.get_stack().top().get_i64();
	vm.get_stack().pop();
	object_buffer.set_i64((buff[0] - buff[1]));
	vm.get_stack().push(object_buffer);
}
void mul64(DracheVM &vm)
{
	if (vm.get_stack().size() < 2)
	{
		logger.elog("vm error: attempted to pop from an empty stack! Exiting. (OPCODE MUL64)");
		std::exit(-1);
	}
	int64_t buff[2] = { 0x00 };
	buff[0] = vm.get_stack().top().get_i64();
	vm.get_stack().pop();
	buff[1] = vm.get_stack().top().get_i64();
	vm.get_stack().pop();
	object_buffer.set_i64((buff[0] * buff[1]));
	vm.get_stack().push(object_buffer);
}
void div64(DracheVM &vm)
{
	if (vm.get_stack().size() < 2)
	{
		logger.elog("vm error: attempted to pop from an empty stack! Exiting. (OPCODE DIV64)");
		std::exit(-1);
	}
	int64_t buff[2] = { 0x00 };
	buff[0] = vm.get_stack().top().get_i64();
	vm.get_stack().pop();
	buff[1] = vm.get_stack().top().get_i64();
	vm.get_stack().pop();
	object_buffer.set_i64((buff[0] / buff[1]));
	vm.get_stack().push(object_buffer);
}

void addf32(DracheVM &vm)
{
	logger.elog("vm error: floating point numbers are not yet supported. Exiting.");
	std::exit(-1);
}
void subf32(DracheVM &vm)
{
	logger.elog("vm error: floating point numbers are not yet supported. Exiting.");
	std::exit(-1);
}
void mulf32(DracheVM &vm)
{
	logger.elog("vm error: floating point numbers are not yet supported. Exiting.");
	std::exit(-1);
}
void divf32(DracheVM &vm)
{
	logger.elog("vm error: floating point numbers are not yet supported. Exiting.");
	std::exit(-1);
}
void addf64(DracheVM &vm)
{
	logger.elog("vm error: floating point numbers are not yet supported. Exiting.");
	std::exit(-1);
}
void subf64(DracheVM &vm)
{
	logger.elog("vm error: floating point numbers are not yet supported. Exiting.");
	std::exit(-1);
}
void mulf64(DracheVM &vm)
{
	logger.elog("vm error: floating point numbers are not yet supported. Exiting.");
	std::exit(-1);
}
void divf64(DracheVM &vm)
{
	logger.elog("vm error: floating point numbers are not yet supported. Exiting.");
	std::exit(-1);
}
