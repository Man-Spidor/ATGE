#pragma once

#include "Scene.h"

namespace ATGE
{
	class SceneManager final
	{
		friend class SceneAttorney;
		friend class MemoryManager;

	private:
		SceneManager() = default;
		SceneManager(const SceneManager& other) = delete;
		SceneManager& operator=(const SceneManager& other) = delete;
		SceneManager(SceneManager&& other) = delete;
		SceneManager& operator=(SceneManager&& other) = delete;
		~SceneManager() = default;

		static void Initialize();

		static void Start();

		static void SetStartupScript(I_SceneScript* pScript);

		// Scene Loop Functions
		static void DrawLoop();
		static void UpdateLoop();

		// TODO: decide if this needs to be a singleton...
	private:
		static SceneManager* s_Instance;
		static SceneManager& Instance()
		{
			ATGE_ASSERT(s_Instance);
			return *s_Instance;
		}

	private:
		Scene m_CurrScene;
	};
}

