#pragma once

#include "Core/Math/Matrix.h"

namespace ATGE
{
	struct TransformComponent final
	{
		TransformComponent() = default;
		TransformComponent(const TransformComponent& other) = default;
		TransformComponent& operator=(const TransformComponent& other) = default;
		TransformComponent(TransformComponent&& other) = default;
		TransformComponent& operator=(TransformComponent&& other) = default;
		~TransformComponent() = default;

		Math::Matrix4x4 m_Transform;
		EntityID m_ID;

		u32 pad[3];
	};
}