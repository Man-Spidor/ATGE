#include "ATGEngine.h"

#include "Memory/MemoryManager.h"

namespace ATGE
{
	ATGEngine::ATGEngine()
	{
	}


	ATGEngine::~ATGEngine()
	{
	}

	void ATGEngine::Run()
	{
		MemoryManager::setEngineArenaSize(g_ATGEArenaSizeDefault);
		MemoryManager::openArena();

		ATGE_ASSERT(Logger::initLogging());
	}
}
