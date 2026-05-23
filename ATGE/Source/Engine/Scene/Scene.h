#pragma once

#include "Managers/DrawManager.h"

namespace ATGE
{
	class I_SceneScript;

	class Scene final
	{
	public:
		Scene();
		Scene(const Scene& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(Scene&& other) = delete;
		~Scene() = default;

		void SetScript(I_SceneScript* pScript);

		void StartScene();
		void EndScene();

		// Per frame Scene Functions
		void Update();
		void Draw();

	private:
		I_SceneScript* m_pScript;

		DrawManager m_DrawMan;
	};
}

