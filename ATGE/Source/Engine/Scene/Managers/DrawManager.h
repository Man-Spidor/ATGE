#pragma once

#include "ModelManager.h"
#include "TransformManager.h"
#include "MaterialManager.h"

#include "Engine/Entity/Components/DrawComponent.h"

namespace ATGE
{
	class DrawManager final
	{
	public:
		DrawManager() = default;
		DrawManager(const DrawManager& other) = delete;
		DrawManager& operator=(const DrawManager& other) = delete;
		DrawManager(DrawManager&& other) = delete;
		DrawManager& operator=(DrawManager&& other) = delete;
		~DrawManager() = default;

		void drawAll();

	private:
		ModelManager m_ModelMan;
		TransformManager m_TransMan;
		MaterialManager m_MatMan;

		SwapbackArray<DrawComponent> m_DrawComps;
	};
}

