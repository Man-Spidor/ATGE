#pragma once

#include <xmmintrin.h>

#include "Constants.h"
#include "EnumDefine.h"

#ifndef ALIGN_16_H
#include "Core/Math/Align16.h"
#endif

#pragma warning( push )
#pragma warning( disable : 5266 ) // 'const' qualifier on return type has no effect

namespace Math
{
	class Matrix4x4;

	class Vector4 final : public Align16
	{
		// Vect and Matrix are highly coupled
		friend Matrix4x4;
		friend class VectApp;

	public:
		Vector4();
		Vector4(const Vector4& other);
		Vector4& operator=(const Vector4& other);
		Vector4(Vector4&& other) noexcept;
		Vector4& operator=(Vector4&& other) noexcept;
		~Vector4() = default;

		Vector4(const __m128& _vm);
		Vector4(const float in_x, const float in_y, const float in_z, const float in_w = 1.0f);

		// Bracket Operators
		inline constexpr float& operator[] (const x_enum) { return this->_x; };
		inline constexpr float& operator[] (const y_enum) { return this->_y; };
		inline constexpr float& operator[] (const z_enum) { return this->_z; };
		inline constexpr float& operator[] (const w_enum) { return this->_w; };

		inline constexpr float operator[] (const x_enum) const { return this->_x; };
		inline constexpr float operator[] (const y_enum) const { return this->_y; };
		inline constexpr float operator[] (const z_enum) const { return this->_z; };
		inline constexpr float operator[] (const w_enum) const { return this->_w; };

		// Accessors 
		inline constexpr float& X() { return this->_x; };
		inline constexpr float& Y() { return this->_y; };
		inline constexpr float& Z() { return this->_z; };
		inline constexpr float& W() { return this->_w; };

		inline constexpr float X() const { return this->_x; };
		inline constexpr float Y() const { return this->_y; };
		inline constexpr float Z() const { return this->_z; };
		inline constexpr float W() const { return this->_w; };

		// add/sub operators
		inline Vector4 operator+(const Vector4& other) const
		{
			return Vector4(_mm_add_ps(this->vm, other.vm));
		}

		inline Vector4 operator-(const Vector4& other) const
		{
			return Vector4(_mm_sub_ps(this->vm, other.vm));
		}

		inline Vector4 operator+() const
		{
			return *this;
		}

		inline Vector4 operator-() const
		{
			return Vector4(_mm_sub_ps(_mm_setzero_ps(), this->vm));
		}

		inline void operator+=(const Vector4& other)
		{
			this->vm = _mm_add_ps(this->vm, other.vm);
		}

		inline void operator-=(const Vector4& other)
		{
			this->vm = _mm_sub_ps(this->vm, other.vm);
		}

		// Multiply operators
		inline Vector4 operator*(const float scale) const
		{
			__m128 s = _mm_set_ps(1.0f, scale, scale, scale);
			return Vector4(_mm_mul_ps(this->vm, s));
		}

		inline friend Vector4 operator*(const float scale, const Vector4& other)
		{
			return other * scale;			
		}

		inline void operator*=(const float scale) 
		{
			__m128 s = _mm_set_ps(1.0f, scale, scale, scale);
			this->vm = _mm_mul_ps(this->vm, s);
		}

		// Vector4 * Matrix
		Vector4 operator*(const Matrix4x4& mat) const;
		Vector4 operator*=(const Matrix4x4& mat);
		
		Vector4 pointMatMult(const Matrix4x4& mat) const;

		// Vector4 functions
		Vector4& norm();
		Vector4 getNorm() const;

		const float dot(const Vector4& other) const;
		const Vector4 cross(const Vector4& other) const;

		const float mag() const;
		const float magSqr() const;

		// const float getAngle(const Vector4& other) const;

		// set
		void set(const float inX, const float inY, const float inZ, const float inW = 1.0f);
		void set(const Vector4& A);

		// comparison
		const bool isEqual(const Vector4& v, const float epsilon = MATH_TOLERANCE) const;
		const bool isZero(const float epsilon = MATH_TOLERANCE) const;

	private:
		// Level 4 complains nameless struct/union ...
		#pragma warning( disable : 4201)
		// anonymous union
		union
		{
			__m128	vm;

			// anonymous struct
			struct
			{
				float _x;
				float _y;
				float _z;
				float _w;
			};
		};
	};
}

#pragma warning( pop )