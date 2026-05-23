#pragma once

#include "Core/Math/Matrix.h"

namespace ATGE
{
	using namespace Math;

	struct Data_InstanceCB
	{
		Matrix4x4 m_WorldMat;
		Matrix4x4 m_WorldInv;
	};
}