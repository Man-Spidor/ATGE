#pragma once

namespace ATGE
{
#ifndef ATGE_UNUSED
#define ATGE_UNUSED(P)          (P)
#endif // ATGE_UNUSED

	// Struct Defines:
	// unsigned primitives
	using u8 = unsigned char;
	using u16 = unsigned short;
	using u32 = unsigned int;
	using u64 = unsigned long long;

	// signed primitives.
	using i8 = signed char;
	using i16 = signed short;
	using i32 = signed int;
	using i64 = signed long long;

	// floating point primitives
	using f32 = float;
	using f64 = double;

	// boolean primitives
	using b32 = int;
	using b8 = bool;

	static_assert(sizeof(u8) == 1);
	static_assert(sizeof(u16) == 2);
	static_assert(sizeof(u32) == 4);
	static_assert(sizeof(u64) == 8);

	static_assert(sizeof(i8) == 1);
	static_assert(sizeof(i16) == 2);
	static_assert(sizeof(i32) == 4);
	static_assert(sizeof(i64) == 8);

	static_assert(sizeof(f32) == 4);
	static_assert(sizeof(f64) == 8);

	static_assert(sizeof(b8) == 1);
	static_assert(sizeof(b32) == 4);

	// Memory Size Defines
	constexpr u32 ATGEMemSizeKB1 = 1024;
	constexpr u32 ATGEMemSizeMB1 = ATGEMemSizeKB1 * 1000;

	// Default Engine Memory Size
	constexpr u32 g_ATGEArenaSizeDefault = ATGEMemSizeKB1 * 1000;
}