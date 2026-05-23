#include "ATGEngine.h"
#include "Engine/Scene/Scripts/I_SceneScript.h"

class TempSceneScript : public ATGE::I_SceneScript
{
	virtual void StartScene()
	{
	};

	virtual void EndScene()
	{
	};
};

int main()
{	
	ATGE::ATGEngine::Initialize(new TempSceneScript);

	ATGE::ATGEngine::Run();
}