#include "SceneManager.h"

namespace ATGE
{
	SceneManager* SceneManager::s_Instance = nullptr;

	void SceneManager::Initialize()
	{
		s_Instance = MemoryManager::allocate<SceneManager>();
	}

	void SceneManager::Start()
	{
		Instance().m_CurrScene.StartScene();
	}

	void SceneManager::SetStartupScript(I_SceneScript* pScript)
	{
		Instance().m_CurrScene.SetScript(pScript);
	}

	void SceneManager::DrawLoop()
	{
		Instance().m_CurrScene.Draw();
	}

	void SceneManager::UpdateLoop()
	{
		Instance().m_CurrScene.Update();
	}
}