#pragma once

#include "Core/Tools/ATGEAssert.h"
#include "Core/Graphics/GraphicsRenderer.h"

namespace ATGE
{
	class ATGEngine
	{
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
		void initialize();
		void shutdown();

	private:
		static ATGEngine* s_instance;
		static ATGEngine& Instance()
		{
			ATGE_ASSERT_DEBUG(s_instance);
			return *s_instance;
		}

	private:
		GraphicsRenderer m_Graphics;
		PlatformInterface m_PlatInterface;
	};
}
