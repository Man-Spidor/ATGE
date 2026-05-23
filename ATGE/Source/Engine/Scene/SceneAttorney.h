#pragma once

#include "SceneManager.h"

namespace ATGE
{
	class SceneAttorney
	{
		friend class ATGEngine;

		static void SetStartupScript(I_SceneScript* pScript) { SceneManager::SetStartupScript(pScript); };
		static void Initialize() { SceneManager::Initialize(); };
		static void Start() { SceneManager::Start(); };

		static void UpdateLoop() { SceneManager::UpdateLoop(); };
		static void DrawLoop() { SceneManager::DrawLoop(); };
	};
}