#pragma once

namespace ATGE
{
	struct DrawComponent final
	{
		DrawComponent() = default;
		DrawComponent(const DrawComponent& other) = default;
		DrawComponent& operator=(const DrawComponent& other) = default;
		DrawComponent(DrawComponent&& other) = default;
		DrawComponent& operator=(DrawComponent&& other) = default;
		~DrawComponent() = default;

		EntityID m_EntityID;
		ModelID m_ModelID;
		TransformID m_TransformID;
		MaterialID m_MaterialID;
		TextureID m_TextureID;
	};
}