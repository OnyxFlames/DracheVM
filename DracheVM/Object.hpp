#pragma once
#include <cstdint>


union Object
{
	char str[512];
	int8_t	i8;
	int16_t i16;
	int32_t i32;
	int64_t i64;
	float	f32;
	double	f64;

};