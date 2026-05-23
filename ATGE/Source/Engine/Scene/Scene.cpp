#include "Scene.h"

#include "Engine/Scene/Scripts/I_SceneScript.h"

namespace ATGE
{
	Scene::Scene() :
		m_pScript(nullptr)
	{
	}

	void Scene::SetScript(I_SceneScript* pScript)
	{
		this->m_pScript = pScript;
	}

	void Scene::StartScene()
	{
		ATGE_ASSERT_MSG(this->m_pScript,"Tried to start scene without setting script scene.");

		this->m_pScript->StartScene();
	}

	void Scene::EndScene()
	{
		ATGE_ASSERT_MSG(this->m_pScript, "Tried to end scene without setting script scene.");
		
		this->m_pScript->EndScene();
	}

	void Scene::Update()
	{
	}

	void Scene::Draw()
	{
		this->m_DrawMan.drawAll();
	}
}