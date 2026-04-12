#include "ATGEngine.h"

#include "Memory/MemoryManager.h"
#include "Platform/PlatformInterface.h"

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


		while (inst.m_PlatInterface.pumpMessages()) {
			InputManager::processInputEvents();
		}

		inst.privShutdown();
	}

	void ATGEngine::privInit()
	{

		ATGE_ASSERT(Logger::initLogging());
		ATGE_ASSERT(this->m_PlatInterface.initPlatform());

		InputManager::Initialize(this->m_PlatInterface.getInputQueue());
	}

	void ATGEngine::privShutdown()
	{
		this->m_PlatInterface.shutdown();

		MemoryManager::closeArena();
		Logger::shutdown();
	}
}
