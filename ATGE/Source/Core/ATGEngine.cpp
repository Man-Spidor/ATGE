#include "ATGEngine.h"

#include "Core/Platform/PlatformInterface.h"

namespace ATGE
{
	ATGEngine* ATGEngine::s_instance;

	ATGEngine::ATGEngine() :
		m_PlatInterface()
	{
	}

	ATGEngine::~ATGEngine()
	{
	}

	void ATGE::ATGEngine::Run()
	{
		ATGE_ASSERT_MSG(s_instance == nullptr, "Cannot call 'ATGEngine::Run' more than one time.");
		s_instance = new ATGEngine();

		ATGEngine& inst = Instance();

		inst.initialize();

		while (inst.m_PlatInterface.pumpMessages()) {
			inst.m_Graphics.renderFrame();
		}

		inst.shutdown();
	}

	void ATGEngine::initialize()
	{
		ATGE_ASSERT(Logger::initLogging());

		ATGE_ASSERT(this->m_PlatInterface.initPlatform());
		ATGE_ASSERT(this->m_Graphics.initGraphics(this->m_PlatInterface.GetPlatform()));
	}

	void ATGEngine::shutdown()
	{
		this->m_Graphics.shutdown();
		this->m_PlatInterface.shutdown();

		Logger::shutdown();

		delete s_instance;
	}
}
