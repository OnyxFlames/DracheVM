#include "VariableManip.hpp"
#include "Logger.hpp"

#include <cstdlib>

extern Logger logger;

Object object_buffer;

void add8(DracheVM &vm)
{
	if (vm.get_stack().size() < 2)
	{
		logger.elog("vm error: attempted to pop from an empty stack! Exiting.");
		std::exit(-1);
	}
	int8_t buff[2] = { 0x00 };
	buff[0] = vm.get_stack().top().i8;
	vm.get_stack().pop();
	buff[1] = vm.get_stack().top().i8;
	vm.get_stack().pop();
	object_buffer.i8 = buff[0] + buff[1];
	vm.get_stack().push(object_buffer);
}
void sub8(DracheVM &vm)
{
	if (vm.get_stack().size() < 2)
	{
		logger.elog("vm error: attempted to pop from an empty stack! Exiting.");
		std::exit(-1);
	}
	int8_t buff[2] = { 0x00 };
	buff[0] = vm.get_stack().top().i8;
	vm.get_stack().pop();
	buff[1] = vm.get_stack().top().i8;
	vm.get_stack().pop();
	object_buffer.i8 = buff[0] - buff[1];
	vm.get_stack().push(object_buffer);
}
void mul8(DracheVM &vm)
{
	if (vm.get_stack().size() < 2)
	{
		logger.elog("vm error: attempted to pop from an empty stack! Exiting.");
		std::exit(-1);
	}
	int8_t buff[2] = { 0x00 };
	buff[0] = vm.get_stack().top().i8;
	vm.get_stack().pop();
	buff[1] = vm.get_stack().top().i8;
	vm.get_stack().pop();
	object_buffer.i8 = buff[0] * buff[1];
	vm.get_stack().push(object_buffer);
}
void div8(DracheVM &vm)
{
	if (vm.get_stack().size() < 2)
	{
		logger.elog("vm error: attempted to pop from an empty stack! Exiting.");
		std::exit(-1);
	}
	int8_t buff[2] = { 0x00 };
	buff[0] = vm.get_stack().top().i8;
	vm.get_stack().pop();
	buff[1] = vm.get_stack().top().i8;
	vm.get_stack().pop();
	object_buffer.i8 = buff[0] / buff[1];
	vm.get_stack().push(object_buffer);
}

void add16(DracheVM &vm)
{
	if (vm.get_stack().size() < 2)
	{
		logger.elog("vm error: attempted to pop from an empty stack! Exiting.");
		std::exit(-1);
	}
	int16_t buff[2] = { 0x00 };
	buff[0] = vm.get_stack().top().i16;
	vm.get_stack().pop();
	buff[1] = vm.get_stack().top().i16;
	vm.get_stack().pop();
	object_buffer.i16 = buff[0] + buff[1];
	vm.get_stack().push(object_buffer);
}
void sub16(DracheVM &vm)
{
	if (vm.get_stack().size() < 2)
	{
		logger.elog("vm error: attempted to pop from an empty stack! Exiting.");
		std::exit(-1);
	}
	int16_t buff[2] = { 0x00 };
	buff[0] = vm.get_stack().top().i16;
	vm.get_stack().pop();
	buff[1] = vm.get_stack().top().i16;
	vm.get_stack().pop();
	object_buffer.i16 = buff[0] - buff[1];
	vm.get_stack().push(object_buffer);
}
void mul16(DracheVM &vm)
{
	if (vm.get_stack().size() < 2)
	{
		logger.elog("vm error: attempted to pop from an empty stack! Exiting.");
		std::exit(-1);
	}
	int16_t buff[2] = { 0x00 };
	buff[0] = vm.get_stack().top().i16;
	vm.get_stack().pop();
	buff[1] = vm.get_stack().top().i16;
	vm.get_stack().pop();
	object_buffer.i16 = buff[0] * buff[1];
	vm.get_stack().push(object_buffer);
}
void div16(DracheVM &vm)
{
	if (vm.get_stack().size() < 2)
	{
		logger.elog("vm error: attempted to pop from an empty stack! Exiting.");
		std::exit(-1);
	}
	int16_t buff[2] = { 0x00 };
	buff[0] = vm.get_stack().top().i16;
	vm.get_stack().pop();
	buff[1] = vm.get_stack().top().i16;
	vm.get_stack().pop();
	object_buffer.i16 = buff[0] / buff[1];
	vm.get_stack().push(object_buffer);
}

void add32(DracheVM &vm)
{
	if (vm.get_stack().size() < 2)
	{
		logger.elog("vm error: attempted to pop from an empty stack! Exiting.");
		std::exit(-1);
	}
	int32_t buff[2] = { 0x00 };
	buff[0] = vm.get_stack().top().i32;
	vm.get_stack().pop();
	buff[1] = vm.get_stack().top().i32;
	vm.get_stack().pop();
	object_buffer.i32 = buff[0] + buff[1];
	vm.get_stack().push(object_buffer);
}
void sub32(DracheVM &vm)
{
	if (vm.get_stack().size() < 2)
	{
		logger.elog("vm error: attempted to pop from an empty stack! Exiting.");
		std::exit(-1);
	}
	int32_t buff[2] = { 0x00 };
	buff[0] = vm.get_stack().top().i32;
	vm.get_stack().pop();
	buff[1] = vm.get_stack().top().i32;
	vm.get_stack().pop();
	object_buffer.i32 = buff[0] - buff[1];
	vm.get_stack().push(object_buffer);
}
void mul32(DracheVM &vm)
{
	if (vm.get_stack().size() < 2)
	{
		logger.elog("vm error: attempted to pop from an empty stack! Exiting.");
		std::exit(-1);
	}
	int32_t buff[2] = { 0x00 };
	buff[0] = vm.get_stack().top().i32;
	vm.get_stack().pop();
	buff[1] = vm.get_stack().top().i32;
	vm.get_stack().pop();
	object_buffer.i32 = buff[0] * buff[1];
	vm.get_stack().push(object_buffer);
}
void div32(DracheVM &vm)
{
	if (vm.get_stack().size() < 2)
	{
		logger.elog("vm error: attempted to pop from an empty stack! Exiting.");
		std::exit(-1);
	}
	int32_t buff[2] = { 0x00 };
	buff[0] = vm.get_stack().top().i32;
	vm.get_stack().pop();
	buff[1] = vm.get_stack().top().i32;
	vm.get_stack().pop();
	object_buffer.i32 = buff[0] / buff[1];
	vm.get_stack().push(object_buffer);
}

void add64(DracheVM &vm)
{
	if (vm.get_stack().size() < 2)
	{
		logger.elog("vm error: attempted to pop from an empty stack! Exiting.");
		std::exit(-1);
	}
	int64_t buff[2] = { 0x00 };
	buff[0] = vm.get_stack().top().i64;
	vm.get_stack().pop();
	buff[1] = vm.get_stack().top().i64;
	vm.get_stack().pop();
	object_buffer.i64 = buff[0] + buff[1];
	vm.get_stack().push(object_buffer);
}
void sub64(DracheVM &vm)
{
	if (vm.get_stack().size() < 2)
	{
		logger.elog("vm error: attempted to pop from an empty stack! Exiting.");
		std::exit(-1);
	}
	int64_t buff[2] = { 0x00 };
	buff[0] = vm.get_stack().top().i64;
	vm.get_stack().pop();
	buff[1] = vm.get_stack().top().i64;
	vm.get_stack().pop();
	object_buffer.i64 = buff[0] - buff[1];
	vm.get_stack().push(object_buffer);
}
void mul64(DracheVM &vm)
{
	if (vm.get_stack().size() < 2)
	{
		logger.elog("vm error: attempted to pop from an empty stack! Exiting.");
		std::exit(-1);
	}
	int64_t buff[2] = { 0x00 };
	buff[0] = vm.get_stack().top().i64;
	vm.get_stack().pop();
	buff[1] = vm.get_stack().top().i64;
	vm.get_stack().pop();
	object_buffer.i64 = buff[0] * buff[1];
	vm.get_stack().push(object_buffer);
}
void div64(DracheVM &vm)
{
	if (vm.get_stack().size() < 2)
	{
		logger.elog("vm error: attempted to pop from an empty stack! Exiting.");
		std::exit(-1);
	}
	int64_t buff[2] = { 0x00 };
	buff[0] = vm.get_stack().top().i64;
	vm.get_stack().pop();
	buff[1] = vm.get_stack().top().i64;
	vm.get_stack().pop();
	object_buffer.i64 = buff[0] / buff[1];
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
