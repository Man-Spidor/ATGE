#pragma once

#include "Constants.h"

namespace Math
{
	class MathUtil
	{
	public:
		static bool isEqual( const float a, const float b, const float epsilon = MATH_TOLERANCE );
		static bool isNotEqual( const float a, const float b, const float epsilon = MATH_TOLERANCE );
		static bool isOne( const float a, const float epsilon = MATH_TOLERANCE );
		static bool isNonZero( const float a, const float epsilon = MATH_TOLERANCE );
		static bool isZero( const float a, const float epsilon = MATH_TOLERANCE );

		static void clampNum(float& num, const float min, const float max);
	};
}