#pragma once

#include "Core/Platform/PlatformInterface.h"

namespace ATGE
{
	class GraphicsRenderer
	{
	public:
		GraphicsRenderer() = default;
		GraphicsRenderer(const GraphicsRenderer& other) = default;
		GraphicsRenderer& operator=(const GraphicsRenderer& other) = default;
		GraphicsRenderer(GraphicsRenderer&& other) = default;
		GraphicsRenderer& operator=(GraphicsRenderer&& other) = default;
		~GraphicsRenderer() = default;

		bool initGraphics(const void* pPlatform);
		void shutdown();

		void renderFrame();

		void onResize();
		void flush();

	private:
		void* m_pGraphicsHandles;
	};
}
