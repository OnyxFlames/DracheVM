#ifndef OBJECT_HPP
#define OBJECT_HPP
#include <cstdint>

enum object_types
{
	type_unknown = 0,
	type_string = 1,
	type_i8,
	type_i16,
	type_i32,
	type_i64,
	type_f32,
	type_f64,
};
/*
	The goal is to keep the 'Object' class as lightweight as possible.
*/
class Object
{
private:
	uint16_t object_type = type_unknown;
	union _Object
	{
		char* str;
		int8_t	i8;
		int16_t i16;
		int32_t i32;
		int64_t i64;
		float	f32;
		double	f64;

	} _object;
public:

	uint16_t get_type() { return object_type; }
	char* get_str() { return _object.str; }
	int8_t get_i8() { return _object.i8; }
	int16_t get_i16() { return _object.i16; }
	int32_t get_i32() { return _object.i32; }
	int64_t get_i64() { return _object.i64; }
	float get_f32() { return _object.f32; }
	double get_f64() { return _object.f64; }

	void set_str(char* val) { object_type = type_string;	_object.str = val; }
	void set_i8(int8_t val) { object_type = type_i8;		_object. i8 = val; }
	void set_i16(int16_t val) { object_type = type_i16;		_object.i16 = val; }
	void set_i32(int32_t val) { object_type = type_i32;		_object.i32 = val; }
	void set_i64(int64_t val) { object_type = type_i64;		_object.i64 = val; }
	void set_f32(float val) { object_type = type_f32;		_object.f32 = val; }
	void set_f64(double val) { object_type = type_f64;		_object.f64 = val; }
};

#endif
