#pragma once

#include "Platform/PlatformInterface.h"

// Member Variables
#include "Engine/Input/InputManager.h"

namespace ATGE
{
	class ATGEngine final
	{
		friend class MemoryManager;

	private:
		ATGEngine();
		ATGEngine(const ATGEngine& other) = default;
		ATGEngine& operator=(const ATGEngine& other) = default;
		ATGEngine(ATGEngine&& other) = default;
		ATGEngine& operator=(ATGEngine&& other) = default;
		~ATGEngine();

	public:
		static void Run();

	private:
		void privInit();
		void privShutdown();

	private:
		static ATGEngine* s_Instance;
		static ATGEngine& Instance()
		{
			ATGE_ASSERT_DEBUG(s_Instance);
			return *s_Instance;
		}

	private:
		PlatformInterface m_PlatInterface;
	};
}

