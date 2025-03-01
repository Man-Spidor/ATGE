#pragma once

#include "Quat.h"

namespace Math
{
	class QuatApp
	{

	public:
		static void Slerp(Quat& result, const Quat& source, const Quat& target, const float slerpFactor);

		static void SlerpArray(Quat* result, const Quat* source, const Quat* target, const float slerpFactor, const int numQuats);


	};
}
