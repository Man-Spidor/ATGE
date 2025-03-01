#pragma once

#include "Vector.h"

#pragma warning( push )
#pragma warning( disable : 5266 ) // 'const' qualifier on return type has no effect

namespace Math
{
	class Matrix4x4 final : public Align16
	{
		// Vect and Matrix are highly coupled
		friend Vector4;

	public:
		Matrix4x4();
		Matrix4x4(const Matrix4x4& other);
		Matrix4x4& operator=(const Matrix4x4& other);
		Matrix4x4(Matrix4x4&& other) noexcept;
		Matrix4x4& operator=(Matrix4x4&& other) noexcept;
		~Matrix4x4() = default;

		// Constructors
		Matrix4x4(const Vector4& tV0, const Vector4& tV1, const Vector4& tV2, const Vector4& tV3);
		Matrix4x4(RotType type, const float angle);
		Matrix4x4(MatrixTransType type, const float tx, const float ty, const float tz);
		Matrix4x4(MatrixScaleType type, const float s);
		Matrix4x4(MatrixScaleType type, const float sx, const float sy, const float sz);

		Matrix4x4(MatrixTransType type, const Vector4& vIn);
		Matrix4x4(Rot3AxisType type, const float angle_0, const float angle_1, const float angle_2);
		Matrix4x4(const RotAxisAngleType type, const Vector4& vAxis, const float angle_radians);
		Matrix4x4(const RotOrientType type, const Vector4& dof, const Vector4& up);
		Matrix4x4(const __m128 _v0, const __m128 _v1, const __m128 _v2, const __m128 _v3);

		explicit Matrix4x4(MatrixSpecialType type);
		// Matrix4x4(const Quat& q);

		// Set 
		void set(const Vector4& V0, const Vector4& V1, const Vector4& V2, const Vector4& V3);
		void set(RotType type, const float angle);

		void set(Rot3AxisType type, const float angle_0, const float angle_1, const float angle_2);
		void set(MatrixTransType type, const Vector4& vIn);
		void set(MatrixScaleType type, const Vector4& vIn);

		void set(const RotAxisAngleType, const Vector4& vAxis, const float angle_radians);
		void set(const RotOrientType, const Vector4& vect_dof, const Vector4& vect_up);
		void set(MatrixTransType type, const float tx, const float ty, const float tz);
		void set(MatrixScaleType type, const float sx, const float sy, const float sz);
		void set(MatrixScaleType type, const float s);
		void set(MatrixSpecialType type);
		// void set(MatrixRowType type, const Vector4& V);
		// void set(const Quat& q);

		// bracket operators
		inline Vector4& operator[] (const enum row_0) { return this->_v0; };
		inline Vector4& operator[] (const enum row_1) { return this->_v1; };
		inline Vector4& operator[] (const enum row_2) { return this->_v2; };
		inline Vector4& operator[] (const enum row_3) { return this->_v3; };

		inline const Vector4& operator[] (const enum row_0) const { return this->_v0; };
		inline const Vector4& operator[] (const enum row_1) const { return this->_v1; };
		inline const Vector4& operator[] (const enum row_2) const { return this->_v2; };
		inline const Vector4& operator[] (const enum row_3) const { return this->_v3; };
		
		inline float& operator[] (const enum m0_enum) { return this->_m0; };
		inline float& operator[] (const enum m1_enum) { return this->_m1; };
		inline float& operator[] (const enum m2_enum) { return this->_m2; };
		inline float& operator[] (const enum m3_enum) { return this->_m3; };
		inline float& operator[] (const enum m4_enum) { return this->_m4; };
		inline float& operator[] (const enum m5_enum) { return this->_m5; };
		inline float& operator[] (const enum m6_enum) { return this->_m6; };
		inline float& operator[] (const enum m7_enum) { return this->_m7; };
		inline float& operator[] (const enum m8_enum) { return this->_m8; };
		inline float& operator[] (const enum m9_enum) { return this->_m9; };
		inline float& operator[] (const enum m10_enum) { return this->_m10; };
		inline float& operator[] (const enum m11_enum) { return this->_m11; };
		inline float& operator[] (const enum m12_enum) { return this->_m12; };
		inline float& operator[] (const enum m13_enum) { return this->_m13; };
		inline float& operator[] (const enum m14_enum) { return this->_m14; };
		inline float& operator[] (const enum m15_enum) { return this->_m15; };
		inline const float operator[] (const enum m0_enum) const { return this->_m0; };
		inline const float operator[] (const enum m1_enum) const { return this->_m1; };
		inline const float operator[] (const enum m2_enum) const { return this->_m2; };
		inline const float operator[] (const enum m3_enum) const { return this->_m3; };
		inline const float operator[] (const enum m4_enum) const { return this->_m4; };
		inline const float operator[] (const enum m5_enum) const { return this->_m5; };
		inline const float operator[] (const enum m6_enum) const { return this->_m6; };
		inline const float operator[] (const enum m7_enum) const { return this->_m7; };
		inline const float operator[] (const enum m8_enum) const { return this->_m8; };
		inline const float operator[] (const enum m9_enum) const { return this->_m9; };
		inline const float operator[] (const enum m10_enum) const { return this->_m10; };
		inline const float operator[] (const enum m11_enum) const { return this->_m11; };
		inline const float operator[] (const enum m12_enum) const { return this->_m12; };
		inline const float operator[] (const enum m13_enum) const { return this->_m13; };
		inline const float operator[] (const enum m14_enum) const { return this->_m14; };
		inline const float operator[] (const enum m15_enum) const { return this->_m15; };

		// accessor	
		inline float& M0() { return this->_m0; };
		inline float& M1() { return this->_m1; };
		inline float& M2() { return this->_m2; };
		inline float& M3() { return this->_m3; };
		inline float& M4() { return this->_m4; };
		inline float& M5() { return this->_m5; };
		inline float& M6() { return this->_m6; };
		inline float& M7() { return this->_m7; };
		inline float& M8() { return this->_m8; };
		inline float& M9() { return this->_m9; };
		inline float& M10() { return this->_m10; };
		inline float& M11() { return this->_m11; };
		inline float& M12() { return this->_m12; };
		inline float& M13() { return this->_m13; };
		inline float& M14() { return this->_m14; };
		inline float& M15() { return this->_m15; };

		inline const float M0() const { return this->_m0; };
		inline const float M1() const { return this->_m1; };
		inline const float M2() const { return this->_m2; };
		inline const float M3() const { return this->_m3; };
		inline const float M4() const { return this->_m4; };
		inline const float M5() const { return this->_m5; };
		inline const float M6() const { return this->_m6; };
		inline const float M7() const { return this->_m7; };
		inline const float M8() const { return this->_m8; };
		inline const float M9() const { return this->_m9; };
		inline const float M10() const { return this->_m10; };
		inline const float M11() const { return this->_m11; };
		inline const float M12() const { return this->_m12; };
		inline const float M13() const { return this->_m13; };
		inline const float M14() const { return this->_m14; };
		inline const float M15() const { return this->_m15; };

		// Matrix functions
		Matrix4x4& T();
		Matrix4x4& inv();
		const Matrix4x4 getT()const;
		const Matrix4x4 getInv() const;

		const float det() const;

		// add/sub operators
		inline Matrix4x4 operator+() const { return Matrix4x4(*this); };

		inline Matrix4x4 operator+(const Matrix4x4& A) const
		{			
			return Matrix4x4(_mm_add_ps(this->_v0.vm, A._v0.vm),
							_mm_add_ps(this->_v1.vm, A._v1.vm),
							_mm_add_ps(this->_v2.vm, A._v2.vm),
							_mm_add_ps(this->_v3.vm, A._v3.vm));
		}

		inline void operator+=(const Matrix4x4& A)
		{			
			this->_v0.vm = _mm_add_ps(this->_v0.vm, A._v0.vm);
			this->_v1.vm = _mm_add_ps(this->_v1.vm, A._v1.vm);
			this->_v2.vm = _mm_add_ps(this->_v2.vm, A._v2.vm);
			this->_v3.vm = _mm_add_ps(this->_v3.vm, A._v3.vm);
		}

		inline Matrix4x4 operator-() const
		{
			return Matrix4x4(_mm_sub_ps(_mm_setzero_ps(), this->_v0.vm),
							_mm_sub_ps(_mm_setzero_ps(), this->_v1.vm),
							_mm_sub_ps(_mm_setzero_ps(), this->_v2.vm),
							_mm_sub_ps(_mm_setzero_ps(), this->_v3.vm));
		}

		inline Matrix4x4 operator-(const Matrix4x4& A) const
		{
			return Matrix4x4(_mm_sub_ps(this->_v0.vm, A._v0.vm),
							_mm_sub_ps(this->_v1.vm, A._v1.vm),
							_mm_sub_ps(this->_v2.vm, A._v2.vm),
							_mm_sub_ps(this->_v3.vm, A._v3.vm));
		}

		inline void operator-=(const Matrix4x4& A)
		{
			this->_v0.vm = _mm_sub_ps(this->_v0.vm, A._v0.vm);
			this->_v1.vm = _mm_sub_ps(this->_v1.vm, A._v1.vm);
			this->_v2.vm = _mm_sub_ps(this->_v2.vm, A._v2.vm);
			this->_v3.vm = _mm_sub_ps(this->_v3.vm, A._v3.vm);
		}

		// Multiply
		inline Matrix4x4 operator*(const float s) const
		{
			__m128 scalar = _mm_set_ps(1.0f, s, s, s);
			return Matrix4x4(_mm_mul_ps(this->_v0.vm, scalar),
							_mm_mul_ps(this->_v1.vm, scalar),
							_mm_mul_ps(this->_v2.vm, scalar),
							_mm_mul_ps(this->_v3.vm, scalar));
		}

		inline friend Matrix4x4 operator*(const float scale, const Matrix4x4& A)
		{
			return Matrix4x4(A._v0 * scale,
							A._v1 * scale,
							A._v2 * scale,
							A._v3 * scale);
		}

		inline void operator*=(const float s)
		{
			__m128 scalar = _mm_set_ps(1.0f, s, s, s);
			this->_v0.vm = _mm_mul_ps(this->_v0.vm, scalar);
			this->_v1.vm = _mm_mul_ps(this->_v1.vm, scalar);
			this->_v2.vm = _mm_mul_ps(this->_v2.vm, scalar);
			this->_v3.vm = _mm_mul_ps(this->_v3.vm, scalar);
		}

		Matrix4x4 operator*(const Matrix4x4& A) const;
		void  operator*=(const Matrix4x4& A);


		// comparison
		const bool isEqual(const Matrix4x4& A, const float epsilon = MATH_TOLERANCE) const;
		const bool isIdentity(const float epsilon = MATH_TOLERANCE) const;
		const bool isRotation(const float epsilon = MATH_TOLERANCE) const;
	
private:
		// Level 4 complains nameless struct/union ...
	#pragma warning( disable : 4201)
		union
		{
			struct
			{
				Vector4 _v0;
				Vector4 _v1;
				Vector4 _v2;
				Vector4 _v3;
			};

			struct
			{
				float _m0;
				float _m1;
				float _m2;
				float _m3;
				float _m4;
				float _m5;
				float _m6;
				float _m7;
				float _m8;
				float _m9;
				float _m10;
				float _m11;
				float _m12;
				float _m13;
				float _m14;
				float _m15;
			};
		};
	};
}

#pragma warning( pop ) 
