#pragma once

#include "Core/Math/Vector.h"

namespace ATGE
{
	using namespace Math;

	struct Material final
	{
		Material() = default;
		Material(const Material& other) = default;
		Material& operator=(const Material& other) = default;
		Material(Material&& other) = default;
		Material& operator=(Material&& other) = default;
		~Material() = default;

		Vector4 m_Ambient;
		Vector4 m_Diffuse;
		Vector4 m_Specular;
	};
}