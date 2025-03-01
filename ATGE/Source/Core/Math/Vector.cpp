#include "Matrix.h"

#include <cassert>
#include <smmintrin.h>

#pragma warning( push )
#pragma warning( disable : 5266 ) // 'const' qualifier on return type has no effect

namespace Math
{
	Vector4::Vector4() :
		vm(_mm_setzero_ps())
	{
	}

	Vector4::Vector4(const Vector4& other) :
		vm(other.vm)
	{
	}

	Vector4& Vector4::operator=(const Vector4& other)
	{
		this->_x = other._x;
		this->_y = other._y;
		this->_z = other._z;
		this->_w = other._w;

		return *this;
	}

	Vector4::Vector4(Vector4&& other) noexcept
	{
		this->_x = other._x;
		this->_y = other._y;
		this->_z = other._z;
		this->_w = other._w;
		
		other.vm = _mm_setzero_ps();
	}

	Vector4& Vector4::operator=(Vector4&& other) noexcept
	{
		this->_x = other._x;
		this->_y = other._y;
		this->_z = other._z;
		this->_w = other._w;

		other.vm = _mm_setzero_ps();

		return *this;
	}

	Vector4::Vector4(const __m128& _vm) :
		vm(_vm)
	{
	}

	Vector4::Vector4(const float in_x, const float in_y, const float in_z, const float in_w) :
		vm(_mm_set_ps(in_x, in_y, in_z, in_w))
	{
	}

	Vector4 Vector4::operator*(const Matrix4x4& mat) const
	{
		__m128  mul0 = _mm_mul_ps(this->vm, _mm_set_ps(mat._v3._x, mat._v2._x, mat._v1._x, mat._v0._x)),// m._v3._x)), // _mm_shuffle_ps(m._v0.vm, m._v0.vm, _MM_SHUFFLE(0, 1, 2, 1))),
				mul1 = _mm_mul_ps(this->vm, _mm_set_ps(mat._v3._y, mat._v2._y, mat._v1._y, mat._v0._y)),// m._v3._y)), // _mm_shuffle_ps(m._v1.vm, m._v1.vm, _MM_SHUFFLE(3, 0, 2, 1))), 
				mul2 = _mm_mul_ps(this->vm, _mm_set_ps(mat._v3._z, mat._v2._z, mat._v1._z, mat._v0._z)),// m._v3._z)), // _mm_shuffle_ps(m._v2.vm, m._v2.vm, _MM_SHUFFLE(3, 0, 2, 1))), 
				mul3 = _mm_mul_ps(this->vm, _mm_set_ps(mat._v3._w, mat._v2._w, mat._v1._w, mat._v0._w));// m._v3._w)); // _mm_shuffle_ps(m._v3.vm, m._v3.vm, _MM_SHUFFLE(3, 0, 2, 1)));
	
		__m128	sum0 = _mm_hadd_ps(mul0, mul0),
				sum1 = _mm_hadd_ps(mul1, mul1), 
				sum2 = _mm_hadd_ps(mul2, mul2),
				sum3 = _mm_hadd_ps(mul3, mul3);
	
		sum0 = _mm_hadd_ps(sum0, sum0);
		sum1 = _mm_hadd_ps(sum1, sum1);
		sum2 = _mm_hadd_ps(sum2, sum2);
		sum3 = _mm_hadd_ps(sum3, sum3);
	
		return Vector4(sum0.m128_f32[0], sum1.m128_f32[0], sum2.m128_f32[0], sum3.m128_f32[0]);
	}

	Vector4 Vector4::operator*=(const Matrix4x4& mat)
	{
		*this = *this * mat;
		
		return *this;
	}

	Vector4 Vector4::pointMatMult(const Matrix4x4& mat) const
	{
		__m128 pVm = _mm_set_ps(1.0f, this->_z, this->_y, this->_x);

		__m128  mul0 = _mm_mul_ps(pVm, _mm_set_ps(mat._v3._x, mat._v2._x, mat._v1._x, mat._v0._x)),// m._v3._x)), // _mm_shuffle_ps(m._v0.vm, m._v0.vm, _MM_SHUFFLE(0, 1, 2, 1))),
				mul1 = _mm_mul_ps(pVm, _mm_set_ps(mat._v3._y, mat._v2._y, mat._v1._y, mat._v0._y)),// m._v3._y)), // _mm_shuffle_ps(m._v1.vm, m._v1.vm, _MM_SHUFFLE(3, 0, 2, 1))), 
				mul2 = _mm_mul_ps(pVm, _mm_set_ps(mat._v3._z, mat._v2._z, mat._v1._z, mat._v0._z)),// m._v3._z)), // _mm_shuffle_ps(m._v2.vm, m._v2.vm, _MM_SHUFFLE(3, 0, 2, 1))), 
				mul3 = _mm_mul_ps(pVm, _mm_set_ps(mat._v3._w, mat._v2._w, mat._v1._w, mat._v0._w));// m._v3._w)); // _mm_shuffle_ps(m._v3.vm, m._v3.vm, _MM_SHUFFLE(3, 0, 2, 1)));
	
		__m128	sum0 = _mm_hadd_ps(mul0, mul0),
				sum1 = _mm_hadd_ps(mul1, mul1), 
				sum2 = _mm_hadd_ps(mul2, mul2),
				sum3 = _mm_hadd_ps(mul3, mul3);
	
		sum0 = _mm_hadd_ps(sum0, sum0);
		sum1 = _mm_hadd_ps(sum1, sum1);
		sum2 = _mm_hadd_ps(sum2, sum2);
		sum3 = _mm_hadd_ps(sum3, sum3);
	
		return Vector4(sum0.m128_f32[0], sum1.m128_f32[0], sum2.m128_f32[0], sum3.m128_f32[0]);
	}

	Vector4& Vector4::norm()
	{
		assert(this->_x != 0.0f || this->_y != 0.0f || this->_z != 0.0f);

		float mag = this->mag();
		__m128 magVM = _mm_set_ps(1.0f, mag, mag, mag);

		this->vm = _mm_div_ps(this->vm, magVM);

		return *this;
	}

	Vector4 Vector4::getNorm() const
	{
		Vector4 temp = *this;
		return temp.norm();
	}

	const float Vector4::dot(const Vector4& other) const
	{
		__m128 mul = _mm_mul_ps(this->vm, other.vm);
		return mul.m128_f32[0] + mul.m128_f32[1] + mul.m128_f32[2];
	}

	const Vector4 Vector4::cross(const Vector4& other) const
	{
		__m128 a_yzx = _mm_shuffle_ps(this->vm, this->vm, _MM_SHUFFLE(3, 0, 2, 1));
		__m128 b_yzx = _mm_shuffle_ps(other.vm, other.vm, _MM_SHUFFLE(3, 0, 2, 1));
		__m128 c = _mm_sub_ps(_mm_mul_ps(this->vm, b_yzx), _mm_mul_ps(a_yzx, other.vm));
		return Vector4(_mm_shuffle_ps(c, c, _MM_SHUFFLE(3, 0, 2, 1)));
	}

	const float Vector4::mag() const
	{
		return sqrtf(this->dot(*this));
	}
	
	const float Vector4::magSqr() const
	{
		return this->dot(*this);
	}

	void Vector4::set(const float inX, const float inY, const float inZ, const float inW)
	{
		this->vm = _mm_set_ps(inW, inZ, inY, inX);
	}

	void Vector4::set(const Vector4& A)
	{
		*this = A;
	}

	const bool Vector4::isEqual(const Vector4& v, const float epsilon) const
	{
		__m128 diff = _mm_sub_ps(this->vm, v.vm);
		__m128 absDiff = _mm_andnot_ps(_mm_set1_ps(-0.0f), diff); // Mask out sign bit for absolute value
		__m128 cmp = _mm_cmple_ps(absDiff, _mm_set1_ps(epsilon));
		return (_mm_movemask_ps(cmp) == 0xF);
	}

	const bool Vector4::isZero(const float epsilon) const
	{
		__m128 absVect = _mm_andnot_ps(_mm_set1_ps(-0.0f), this->vm); // Mask out sign bit for absolute value
		__m128 cmp = _mm_cmple_ps(absVect, _mm_set1_ps(epsilon));
		return (_mm_movemask_ps(cmp) == 0xF);
	}
}

#pragma warning( pop )