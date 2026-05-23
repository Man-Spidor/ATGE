#include "ATGEngine.h"

#include "Core/Memory/MemoryManager.h"
#include "Core/Platform/PlatformInterface.h"

#include "Engine/Tools/TimeAttorney.h"
#include "Engine/Scene/SceneAttorney.h"

namespace ATGE
{
	ATGEngine* ATGEngine::s_Instance;

	ATGEngine::ATGEngine() :
		m_PlatInterface()
	{
	}

	ATGEngine::~ATGEngine()
	{
	}

	void ATGEngine::Initialize(I_SceneScript* pScript)
	{
		ATGE_ASSERT(Logger::initLogging());
		ATGE_ASSERT(MemoryManager::initMemMan());

		MemoryManager::setEngineArenaSize(g_ATGEArenaSizeDefault);
		ATGE_ASSERT(MemoryManager::OpenArena());

		// Create the engine instance and initialize everything else after
		s_Instance = MemoryManager::allocate<ATGEngine>();
		ATGEngine& inst = Instance();
		inst.privInit();

		SceneAttorney::SetStartupScript(pScript);
	}

	void ATGEngine::Run()
	{
		SceneAttorney::Start();

		ATGEngine& inst = Instance();
		inst.m_Timer.Reset();

		while (inst.m_PlatInterface.pumpMessages()) {
			inst.m_Timer.Tick();
#ifdef _DEBUG
			inst.m_PlatInterface.calculateFrameStats(inst.m_Timer);
#endif // _DEBUG

			TimeAttorney::ProcessTime();

			InputManager::ProcessInputEvents();
			SceneAttorney::UpdateLoop();
		}

		inst.privShutdown();
	}

	const float ATGEngine::GetTimeInSeconds()
	{
		return Instance().m_Timer.TotalTime();
	}

	void ATGEngine::privInit()
	{		
		ATGE_ASSERT(this->m_PlatInterface.initPlatform());

		TimeAttorney::Initialize();
		InputManager::Initialize(this->m_PlatInterface.getInputQueue());
		
		SceneAttorney::Initialize();
	}

	void ATGEngine::privShutdown()
	{
		this->m_PlatInterface.shutdown();

		MemoryManager::CloseArena();
		Logger::shutdown();
	}
}
