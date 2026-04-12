#include "ATGEngine.h"

#include "Core/Memory/MemoryManager.h"
#include "Core/Platform/PlatformInterface.h"

#include "Engine/Tools/TimeAttorney.h"

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

	void ATGEngine::Run()
	{
		MemoryManager::setEngineArenaSize(g_ATGEArenaSizeDefault);
		MemoryManager::openArena();

		s_Instance = MemoryManager::allocate<ATGEngine>();

		ATGEngine& inst = Instance();

		inst.privInit();

		inst.m_Timer.Reset();
		while (inst.m_PlatInterface.pumpMessages()) {
			inst.m_Timer.Tick();
#ifdef _DEBUG
			inst.m_PlatInterface.calculateFrameStats(inst.m_Timer);
#endif // _DEBUG

			TimeAttorney::ProcessTime();

			InputManager::processInputEvents();
		}

		inst.privShutdown();
	}

	const float ATGEngine::GetTimeInSeconds()
	{
		return Instance().m_Timer.TotalTime();
	}

	void ATGEngine::privInit()
	{

		ATGE_ASSERT(Logger::initLogging());
		ATGE_ASSERT(this->m_PlatInterface.initPlatform());

		TimeAttorney::Initialize();
		InputManager::Initialize(this->m_PlatInterface.getInputQueue());
	}

	void ATGEngine::privShutdown()
	{
		this->m_PlatInterface.shutdown();

		MemoryManager::closeArena();
		Logger::shutdown();
	}
}
