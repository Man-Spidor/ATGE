#pragma once

#include "Core/Platform/PlatformInterface.h"

// Member Variables
#include "Core/Tools/GameTimer.h"
#include "Engine/Input/InputManager.h"

namespace ATGE
{
	class I_SceneScript;

	class ATGEngine final
	{
		friend class ATGEAttorney;
		
	public:
		explicit ATGEngine(MemoryManager::AllocKey);
	
	private:
		ATGEngine(const ATGEngine& other) = default;
		ATGEngine& operator=(const ATGEngine& other) = default;
		ATGEngine(ATGEngine&& other) = default;
		ATGEngine& operator=(ATGEngine&& other) = default;
		~ATGEngine();

	public:

		// TODO: find a neater way to do this
		static void Initialize(I_SceneScript* pScript);
		static void Run();

	private:
		static const float GetTimeInSeconds();

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
		GameTimer m_Timer;
		PlatformInterface m_PlatInterface;
	};
}

