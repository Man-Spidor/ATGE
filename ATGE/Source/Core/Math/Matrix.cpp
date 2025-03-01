#include "Matrix.h"

#include "MatrixMacros.h"

#pragma warning( push )
#pragma warning( disable : 5266 ) // 'const' qualifier on return type has no effect

namespace Math
{
	Matrix4x4::Matrix4x4() : 
		_v0(), 
		_v1(), 
		_v2(), 
		_v3() 
	{
	}

	Matrix4x4::Matrix4x4(const Matrix4x4& other) :
		_v0(other._v0),
		_v1(other._v1), 
		_v2(other._v2), 
		_v3(other._v3)
	{
	}

	Matrix4x4& Matrix4x4::operator=(const Matrix4x4& other)
	{
		this->_v0 = other._v0;
		this->_v1 = other._v1;
		this->_v2 = other._v2;
		this->_v3 = other._v3;
		return *this;
	}

	Matrix4x4::Matrix4x4(Matrix4x4&& other) noexcept
	{
		this->_v0 = other._v0;
		this->_v1 = other._v1;
		this->_v2 = other._v2;
		this->_v3 = other._v3;
		
		__m128 zero = _mm_setzero_ps();
		other._v0.vm = zero;
		other._v1.vm = zero;
		other._v2.vm = zero;
		other._v3.vm = zero;
	}

	Matrix4x4& Matrix4x4::operator=(Matrix4x4&& other) noexcept
	{
		this->_v0 = other._v0;
		this->_v1 = other._v1;
		this->_v2 = other._v2;
		this->_v3 = other._v3;

		__m128 zero = _mm_setzero_ps();
		other._v0.vm = zero;
		other._v1.vm = zero;
		other._v2.vm = zero;
		other._v3.vm = zero;

		return *this;
	}

	Matrix4x4::Matrix4x4(const Vector4& tV0, const Vector4& tV1, const Vector4& tV2, const Vector4& tV3) :
		_v0(tV0),
		_v1(tV1),
		_v2(tV2),
		_v3(tV3)
	{
	}

	Matrix4x4::Matrix4x4(RotType type, const float angle)
	{
		this->set(type, angle);
	}

	Matrix4x4::Matrix4x4(MatrixTransType type, const float tx, const float ty, const float tz)
	{
		this->set(type, tx, ty, tz);
	}

	Matrix4x4::Matrix4x4(MatrixScaleType type, const float s)
	{
		this->set(type, s);
	}

	Matrix4x4::Matrix4x4(MatrixScaleType type, const float sx, const float sy, const float sz)
	{
		MATH_UNUSED(type);

		this->_v0 = Vector4(sx, 0.0f, 0.0f, 0.0f);
		this->_v1 = Vector4(0.0f, sy, 0.0f, 0.0f);
		this->_v2 = Vector4(0.0f, 0.0f, sz, 0.0f);
		this->_v3 = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
	}

	Matrix4x4::Matrix4x4(MatrixTransType type, const Vector4& vIn)
	{
		this->set(type, vIn);
	}

	Matrix4x4::Matrix4x4(Rot3AxisType type, const float angle_0, const float angle_1, const float angle_2)
	{
		this->set(type, angle_0, angle_1, angle_2);
	}

	Matrix4x4::Matrix4x4(const RotAxisAngleType type, const Vector4& vAxis, const float angle_radians)
	{
		this->set(type, vAxis, angle_radians);
	}

	Matrix4x4::Matrix4x4(const RotOrientType type, const Vector4& dof, const Vector4& up)
	{
		this->set(type, dof, up);
	}

	Matrix4x4::Matrix4x4(const __m128 _v0, const __m128 _v1, const __m128 _v2, const __m128 _v3) :
		_v0(_v0),
		_v1(_v1),
		_v2(_v2),
		_v3(_v3)
	{
	}

	Matrix4x4::Matrix4x4(MatrixSpecialType type)
	{
		this->set(type);
	}

	void Matrix4x4::set(const Vector4& V0, const Vector4& V1, const Vector4& V2, const Vector4& V3)
	{
		this->_v0 = V0;
		this->_v1 = V1;
		this->_v2 = V2;
		this->_v3 = V3;
	}

	void Matrix4x4::set(RotType type, const float angle)
	{
		float c = std::cosf(angle);
		float s = std::sinf(angle);

		switch (type) {
		case ROT_X:
			this->_v0 = Vector4(1, 0, 0, 0);
			this->_v1 = Vector4(0, c, s, 0);
			this->_v2 = Vector4(0, -s, c, 0);
			this->_v3 = Vector4(0, 0, 0, 1);
			break;
		case ROT_Y:
			this->_v0 = Vector4(c, 0, -s, 0);
			this->_v1 = Vector4(0, 1, 0, 0);
			this->_v2 = Vector4(s, 0, c, 0);
			this->_v3 = Vector4(0, 0, 0, 1);
			break;
		case ROT_Z:
			this->_v0 = Vector4(c, s, 0, 0);
			this->_v1 = Vector4(-s, c, 0, 0);
			this->_v2 = Vector4(0, 0, 1, 0);
			this->_v3 = Vector4(0, 0, 0, 1);
			break;
		}
	}

	void Matrix4x4::set(Rot3AxisType type, const float angle_0, const float angle_1, const float angle_2)
	{
		MATH_UNUSED(type);

		Matrix4x4 rx = Matrix4x4(ROT_X, angle_0);
		Matrix4x4 ry = Matrix4x4(ROT_Y, angle_1);
		Matrix4x4 rz = Matrix4x4(ROT_Z, angle_2);

		// *this = rx * ry * rz;
	}

	void Matrix4x4::set(MatrixTransType type, const Vector4& vIn)
	{
		MATH_UNUSED(type);

		this->_v0 = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
		this->_v1 = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
		this->_v2 = Vector4(0.0f, 0.0f, 1.0f, 0.0f);
		this->_v3 = vIn;
	}

	void Matrix4x4::set(MatrixScaleType type, const Vector4& vIn)
	{
		this->set(type, vIn._x, vIn._y, vIn._z);
	}

	void Matrix4x4::set(const RotAxisAngleType, const Vector4& vAxis, const float angle_radians)
	{
		Vector4 r = vAxis.getNorm();

		const float c = std::cosf(angle_radians), s = std::sinf(angle_radians);

		const float t = 1.0f - std::cosf(angle_radians);
		// const float x = vAxis.X(), y = vAxis.Y(), z = vAxis.Z();
		const float x = r.X(), y = r.Y(), z = r.Z();

		this->_v0 = Vector4((t * x * x) + c, (t * x * y) + (s * z), (t * x * z) - (s * y), 0.0f);
		this->_v1 = Vector4((t * x * y) - (s * z), (t * y * y) + c, (t * y * z) + (s * x), 0.0f);
		this->_v2 = Vector4((t * x * z) + (s * y), (t * y * z) - (s * x), (t * z * z) + c, 0.0f);
		this->_v3 = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
	}

	void Matrix4x4::set(const RotOrientType type, const Vector4& vect_dof, const Vector4& vect_up)
	{
		MATH_UNUSED(type);

		Vector4 forward = vect_dof.getNorm();
		Vector4 right = vect_up.cross(forward).getNorm();
		Vector4 up = forward.cross(right).getNorm();

		this->_v0 = Vector4(right.X(), right.Y(), right.Z(), 0.0f);
		this->_v1 = Vector4(up.X(), up.Y(), up.Z(), 0.0f);
		this->_v2 = Vector4(forward.X(), forward.Y(), forward.Z(), 0.0f);
		this->_v3 = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
	}

	void Matrix4x4::set(MatrixTransType type, const float tx, const float ty, const float tz)
	{
		this->set(type, Vector4(tx, ty, tz));
	}

	void Matrix4x4::set(MatrixScaleType type, const float sx, const float sy, const float sz)
	{
		MATH_UNUSED(type);

		this->_v0 = Vector4(sx, 0.0f, 0.0f, 0.0f);
		this->_v1 = Vector4(0.0f, sy, 0.0f, 0.0f);
		this->_v2 = Vector4(0.0f, 0.0f, sz, 0.0f);
		this->_v3 = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
	}

	void Matrix4x4::set(MatrixScaleType type, const float s)
	{
		MATH_UNUSED(type);

		this->_v0 = Vector4(s, 0.0f, 0.0f, 0.0f);
		this->_v1 = Vector4(0.0f, s, 0.0f, 0.0f);
		this->_v2 = Vector4(0.0f, 0.0f, s, 0.0f);
		this->_v3 = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
	}

	void Matrix4x4::set(MatrixSpecialType type)
	{
		if (type == IDENTITY) {
			this->_v0 = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
			this->_v1 = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
			this->_v2 = Vector4(0.0f, 0.0f, 1.0f, 0.0f);
			this->_v3 = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
		}
		else if (type == ZERO) {
			this->_v0 = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
			this->_v1 = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
			this->_v2 = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
			this->_v3 = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
		}
	}

	Matrix4x4& Matrix4x4::T()
	{
		_MM_TRANSPOSE4_PS(this->_v0.vm, this->_v1.vm, this->_v2.vm, this->_v3.vm);
		return *this;
	}

	Matrix4x4& Matrix4x4::inv()
	{
		// use block matrix method
		// A is a matrix, then i(A) or iA means inverse of A, A# (or A_ in code) means adjugate of A, |A| (or detA in code) is determinant, tr(A) is trace

		// sub matrices
		__m128 A = VecShuffle_0101(this->_v0.vm, this->_v1.vm);
		__m128 B = VecShuffle_2323(this->_v0.vm, this->_v1.vm);
		__m128 C = VecShuffle_0101(this->_v2.vm, this->_v3.vm);
		__m128 D = VecShuffle_2323(this->_v2.vm, this->_v3.vm);

		// determinant as (|A| |B| |C| |D|)
		__m128 detSub = _mm_sub_ps(
			_mm_mul_ps(VecShuffle(this->_v0.vm, this->_v2.vm, 0, 2, 0, 2), VecShuffle(this->_v1.vm, this->_v3.vm, 1, 3, 1, 3)),
			_mm_mul_ps(VecShuffle(this->_v0.vm, this->_v2.vm, 1, 3, 1, 3), VecShuffle(this->_v1.vm, this->_v3.vm, 0, 2, 0, 2))
		);

		__m128 detA = VecSwizzle1(detSub, 0);
		__m128 detB = VecSwizzle1(detSub, 1);
		__m128 detC = VecSwizzle1(detSub, 2);
		__m128 detD = VecSwizzle1(detSub, 3);

		// let iM = 1/|M| * | X  Y |
		//                  | Z  W |

		// D#C
		__m128 D_C = Mat2AdjMul(D, C);
		// A#B
		__m128 A_B = Mat2AdjMul(A, B);
		// X# = |D|A - B(D#C)
		__m128 X_ = _mm_sub_ps(_mm_mul_ps(detD, A), Mat2Mul(B, D_C));
		// W# = |A|D - C(A#B)
		__m128 W_ = _mm_sub_ps(_mm_mul_ps(detA, D), Mat2Mul(C, A_B));

		// |M| = |A|*|D| + ... (continue later)
		__m128 detM = _mm_mul_ps(detA, detD);

		// Y# = |B|C - D(A#B)#
		__m128 Y_ = _mm_sub_ps(_mm_mul_ps(detB, C), Mat2MulAdj(D, A_B));
		// Z# = |C|B - A(D#C)#
		__m128 Z_ = _mm_sub_ps(_mm_mul_ps(detC, B), Mat2MulAdj(A, D_C));

		// |M| = |A|*|D| + |B|*|C| ... (continue later)
		detM = _mm_add_ps(detM, _mm_mul_ps(detB, detC));

		// tr((A#B)(D#C))
		__m128 tr = _mm_mul_ps(A_B, VecSwizzle(D_C, 0, 2, 1, 3));
		tr = _mm_hadd_ps(tr, tr);
		tr = _mm_hadd_ps(tr, tr);
		// |M| = |A|*|D| + |B|*|C| - tr((A#B)(D#C)
		detM = _mm_sub_ps(detM, tr);

		const __m128 adjSignMask = _mm_setr_ps(1.f, -1.f, -1.f, 1.f);
		// (1/|M|, -1/|M|, -1/|M|, 1/|M|)
		__m128 rDetM = _mm_div_ps(adjSignMask, detM);

		X_ = _mm_mul_ps(X_, rDetM);
		Y_ = _mm_mul_ps(Y_, rDetM);
		Z_ = _mm_mul_ps(Z_, rDetM);
		W_ = _mm_mul_ps(W_, rDetM);

		// apply adjugate and store, here we combine adjugate shuffle and store shuffle
		this->_v0.vm = VecShuffle(X_, Y_, 3, 1, 3, 1);
		this->_v1.vm = VecShuffle(X_, Y_, 2, 0, 2, 0);
		this->_v2.vm = VecShuffle(Z_, W_, 3, 1, 3, 1);
		this->_v3.vm = VecShuffle(Z_, W_, 2, 0, 2, 0);

		return *this;
	}

	const Matrix4x4 Matrix4x4::getT() const
	{
		Matrix4x4 result = *this;
		return result.T();
	}

	const Matrix4x4 Matrix4x4::getInv() const
	{
		Matrix4x4 result = *this;
		return result.inv();
	}

	const float Matrix4x4::det() const
	{
		// Compute the determinant using SIMD operations
		// Assume column-major storage for this implementation

		// | A | = a11(a22a33a44 + a23a34a42 + a24a32a43 - a24a33a42 - a22a34a43 - a23a32a44)
		float m0 = this->_v0.X(), m1 = this->_v0.Y(), m2 = this->_v0.Z(), m3 = this->_v0.W();
		float m4 = this->_v1.X(), m5 = this->_v1.Y(), m6 = this->_v1.Z(), m7 = this->_v1.W();
		float m8 = this->_v2.X(), m9 = this->_v2.Y(), m10 = this->_v2.Z(), m11 = this->_v2.W();
		float m12 = this->_v3.X(), m13 = this->_v3.Y(), m14 = this->_v3.Z(), m15 = this->_v3.W();

		float det = m0 * (m5 * (m10 * m15 - m11 * m14) - m6 * (m9 * m15 - m11 * m13) + m7 * (m9 * m14 - m10 * m13)) -
					m1 * (m4 * (m10 * m15 - m11 * m14) - m6 * (m8 * m15 - m11 * m12) + m7 * (m8 * m14 - m10 * m12)) +
					m2 * (m4 * (m9 * m15 - m11 * m13) - m5 * (m8 * m15 - m11 * m12) + m7 * (m8 * m13 - m9 * m12)) -
					m3 * (m4 * (m9 * m14 - m10 * m13) - m5 * (m8 * m14 - m10 * m12) + m6 * (m8 * m13 - m9 * m12));

		return det;
	}

	Matrix4x4 Matrix4x4::operator*(const Matrix4x4& A) const
	{
		Matrix4x4 result;

		__m128 row = _mm_set_ps(A._v3._x, A._v2._x, A._v1._x, A._v0._x);

		__m128  mul0 = _mm_mul_ps(this->_v0.vm, row),
			mul1 = _mm_mul_ps(this->_v1.vm, row),
			mul2 = _mm_mul_ps(this->_v2.vm, row),
			mul3 = _mm_mul_ps(this->_v3.vm, row);

		__m128	sum0 = _mm_hadd_ps(mul0, mul0),
			sum1 = _mm_hadd_ps(mul1, mul1),
			sum2 = _mm_hadd_ps(mul2, mul2),
			sum3 = _mm_hadd_ps(mul3, mul3);

		sum0 = _mm_hadd_ps(sum0, sum0);
		sum1 = _mm_hadd_ps(sum1, sum1);
		sum2 = _mm_hadd_ps(sum2, sum2);
		sum3 = _mm_hadd_ps(sum3, sum3);

		result._v0._x = sum0.m128_f32[0];
		result._v1._x = sum1.m128_f32[0];
		result._v2._x = sum2.m128_f32[0];
		result._v3._x = sum3.m128_f32[0];

		row = _mm_set_ps(A._v3._y, A._v2._y, A._v1._y, A._v0._y);

		mul0 = _mm_mul_ps(this->_v0.vm, row);
		mul1 = _mm_mul_ps(this->_v1.vm, row);
		mul2 = _mm_mul_ps(this->_v2.vm, row);
		mul3 = _mm_mul_ps(this->_v3.vm, row);

		sum0 = _mm_hadd_ps(mul0, mul0);
		sum1 = _mm_hadd_ps(mul1, mul1);
		sum2 = _mm_hadd_ps(mul2, mul2);
		sum3 = _mm_hadd_ps(mul3, mul3);

		sum0 = _mm_hadd_ps(sum0, sum0);
		sum1 = _mm_hadd_ps(sum1, sum1);
		sum2 = _mm_hadd_ps(sum2, sum2);
		sum3 = _mm_hadd_ps(sum3, sum3);

		result._v0._y = sum0.m128_f32[0];
		result._v1._y = sum1.m128_f32[0];
		result._v2._y = sum2.m128_f32[0];
		result._v3._y = sum3.m128_f32[0];

		row = _mm_set_ps(A._v3._z, A._v2._z, A._v1._z, A._v0._z);

		mul0 = _mm_mul_ps(this->_v0.vm, row);
		mul1 = _mm_mul_ps(this->_v1.vm, row);
		mul2 = _mm_mul_ps(this->_v2.vm, row);
		mul3 = _mm_mul_ps(this->_v3.vm, row);

		sum0 = _mm_hadd_ps(mul0, mul0);
		sum1 = _mm_hadd_ps(mul1, mul1);
		sum2 = _mm_hadd_ps(mul2, mul2);
		sum3 = _mm_hadd_ps(mul3, mul3);

		sum0 = _mm_hadd_ps(sum0, sum0);
		sum1 = _mm_hadd_ps(sum1, sum1);
		sum2 = _mm_hadd_ps(sum2, sum2);
		sum3 = _mm_hadd_ps(sum3, sum3);

		result._v0._z = sum0.m128_f32[0];
		result._v1._z = sum1.m128_f32[0];
		result._v2._z = sum2.m128_f32[0];
		result._v3._z = sum3.m128_f32[0];

		row = _mm_set_ps(A._v3._w, A._v2._w, A._v1._w, A._v0._w);

		mul0 = _mm_mul_ps(this->_v0.vm, row);
		mul1 = _mm_mul_ps(this->_v1.vm, row);
		mul2 = _mm_mul_ps(this->_v2.vm, row);
		mul3 = _mm_mul_ps(this->_v3.vm, row);

		sum0 = _mm_hadd_ps(mul0, mul0);
		sum1 = _mm_hadd_ps(mul1, mul1);
		sum2 = _mm_hadd_ps(mul2, mul2);
		sum3 = _mm_hadd_ps(mul3, mul3);

		sum0 = _mm_hadd_ps(sum0, sum0);
		sum1 = _mm_hadd_ps(sum1, sum1);
		sum2 = _mm_hadd_ps(sum2, sum2);
		sum3 = _mm_hadd_ps(sum3, sum3);

		result._v0._w = sum0.m128_f32[0];
		result._v1._w = sum1.m128_f32[0];
		result._v2._w = sum2.m128_f32[0];
		result._v3._w = sum3.m128_f32[0];

		return result;
	}

	void Matrix4x4::operator*=(const Matrix4x4& A)
	{
		*this = *this * A;
	}

	const bool Matrix4x4::isEqual(const Matrix4x4& A, const float epsilon) const
	{
		return	this->_v0.isEqual(A._v0, epsilon) &&
				this->_v1.isEqual(A._v1, epsilon) &&
				this->_v2.isEqual(A._v2, epsilon) &&
				this->_v3.isEqual(A._v3, epsilon);
	}

	const bool Matrix4x4::isIdentity(const float epsilon) const
	{
		return this->isEqual(Matrix4x4(IDENTITY), epsilon);
	}

	const bool Matrix4x4::isRotation(const float epsilon) const
	{
		Matrix4x4 transpose = this->getT();
		Matrix4x4 identity(IDENTITY);

		Matrix4x4 result = transpose * (*this);
		return result.isEqual(identity, epsilon);
	}
}

#pragma warning( pop )