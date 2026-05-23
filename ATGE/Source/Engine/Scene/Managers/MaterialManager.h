#pragma once

#include "DataStructures/SwapbackArray.h"

#include "Engine/Entity/Components/MaterialComponent.h"

namespace ATGE
{
	class MaterialManager final
	{
	public:
		MaterialManager() = default;
		MaterialManager(const MaterialManager& other) = default;
		MaterialManager& operator=(const MaterialManager& other) = default;
		MaterialManager(MaterialManager&& other) = default;
		MaterialManager& operator=(MaterialManager&& other) = default;
		~MaterialManager() = default;

		void addMaterial(const Material& mat);
		
		const Material& getMaterial(MaterialID mID) const;

	private:
		SwapbackArray<MaterialComponent> m_MatComps;
		MaterialID m_CurrID;
	};
}

