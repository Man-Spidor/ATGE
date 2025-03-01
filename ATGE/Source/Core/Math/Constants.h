#pragma once

#define MATH_UNUSED(x)	(x)

namespace Math
{
	/// @var MATH_ZERO
	///  Define for 0.0f
	constexpr float MATH_ZERO = 0.0f;

	///@var MATH_ONE
	/// Define for 1.0f
	constexpr float MATH_ONE = 1.0f;

	/// var MATH_PI
	/// Define for PI radians
	constexpr float MATH_PI = 3.1415926535f;

	/// var MATH_2PI
	/// Define for 2*PI radians
	constexpr float MATH_2PI = 6.2831853071f;

	/// var MATH_PI2
	/// Define for PI/2 radians
	constexpr float MATH_PI2 = 1.5707963268f;

	/// var MATH_PI3
	/// Define for PI/3 radians
	constexpr float MATH_PI3 = 1.0471975512f;

	/// var MATH_PI4
	/// Define for PI/4 radians
	constexpr float MATH_PI4 = 0.7853981633f;

	/// var MATH_PI8
	/// Define for PI/8 radians
	constexpr float MATH_PI8 = 0.3926990816f;

	/// var MATH_2PI3
	/// Define for 2/3*PI radians
	constexpr float MATH_2PI3 = 2.0943951023f;

	/// var MATH_3PI4
	/// Define for 3/4*PI radians
	constexpr float MATH_3PI4 = 2.3561944901f;

	/// var MATH_2PI8
	/// Define for 2/8*PI radians
	constexpr float MATH_2PI8 = 0.7853981633f;

	/// var MATH_3PI8
	/// Define for 3/8*PI radians
	constexpr float MATH_3PI8 = 1.1780972451f;

	/// var MATH_4PI8
	/// Define for 4/8*PI radians
	constexpr float MATH_4PI8 = 1.5707963268f;

	/// var MATH_5PI8
	/// Define for 5/8*PI radians
	constexpr float MATH_5PI8 = 1.9634954085f;

	/// var MATH_6PI8
	/// Define for 6/8*PI radians
	constexpr float MATH_6PI8 = 2.3561944901f;

	/// var MATH_7PI8
	/// Define for 7/8*PI radians
	constexpr float MATH_7PI8 = 2.7488935718f;

	/// var MATH_180_PI
	/// Define for 180 degrees / PI radians
	constexpr float MATH_180_PI = 57.2957795147f;

	/// var MATH_PI_180
	/// Define for PI radians / 180 degrees
	constexpr float MATH_PI_180 = 0.0174532925f;

	/// var MATH_INV_SQRT_2
	/// Constant for 1/sqrt(2)
	constexpr float MATH_INV_SQRT_2 = 0.707106781188f;

	/// var MATH_TOLERANCE
	/// Default epsilon in Math libraries
	constexpr float MATH_TOLERANCE = 0.0001f;
}