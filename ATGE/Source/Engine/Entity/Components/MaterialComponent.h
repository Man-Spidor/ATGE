#pragma once

#include "Graphics/Material.h"

namespace ATGE
{
	struct MaterialComponent final
	{
	public:
		MaterialComponent() = default;
		MaterialComponent(const MaterialComponent& other) = default;
		MaterialComponent& operator=(const MaterialComponent& other) = default;
		MaterialComponent(MaterialComponent&& other) = default;
		MaterialComponent& operator=(MaterialComponent&& other) = default;
		~MaterialComponent() = default;

		MaterialComponent(const Material& _mat, MaterialID _mID);

		Material m_Material;
		MaterialID m_MaterialID;

		u32 pad[3];
	};
}