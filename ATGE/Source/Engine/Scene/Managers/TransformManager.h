#pragma once

#include "DataStructures/SwapbackArray.h"
#include "Engine/Entity/Components/TransformComponent.h"

namespace ATGE
{
	class TransformManager final
	{
	public:
		TransformManager() = default;
		TransformManager(const TransformManager& other) = default;
		TransformManager& operator=(const TransformManager& other) = default;
		TransformManager(TransformManager&& other) = default;
		TransformManager& operator=(TransformManager&& other) = default;
		~TransformManager() = default;

		const TransformComponent& getTransform(EntityID id) const;

	private:
		SwapbackArray<TransformComponent> m_TransComponents;
	};
}

