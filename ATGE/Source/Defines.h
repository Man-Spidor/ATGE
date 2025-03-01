#pragma once

namespace ATGE
{
	using uchar = unsigned char;
	using ushort = unsigned short;
	using uint = unsigned int;
	using ulong = unsigned long long;

#define ATGE_UNUSED(P)          (P)

	static_assert(sizeof(uchar) == 1);
	static_assert(sizeof(ushort) == 2);
	static_assert(sizeof(uint) == 4);
	static_assert(sizeof(ulong) == 8);
}