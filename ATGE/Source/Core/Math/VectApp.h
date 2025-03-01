#pragma once

#include "Vector.h"

namespace Math
{
	class VectApp
	{
	public:
		// lerp
		static void Lerp(Vector4& out, const Vector4& a, const Vector4& b, const float t);
		// lerp array
		static void LerpArray(Vector4* out, const Vector4* a, const Vector4* b, const float t, const int numVects);

		static void SumArray(Vector4& out, const Vector4* array, const int numVects);

		static void GetRandPoint(Vector4& out, const Vector4& anchor, int randOffset);
	};
}
