#pragma once

#include "InputQueue.h"

namespace ATGE 
{
	struct WindowConfig;
	class GameTimer;

	class PlatformInterface
	{
	public:
		PlatformInterface() = default;
		PlatformInterface(const PlatformInterface& other) = default;
		PlatformInterface& operator=(const PlatformInterface& other) = default;
		PlatformInterface(PlatformInterface&& other) = default;
		PlatformInterface& operator=(PlatformInterface&& other) = default;
		~PlatformInterface() = default;

		bool initPlatform();
		bool initPlatform(const WindowConfig& config);
		bool pumpMessages();
		void shutdown();

		void calculateFrameStats(const GameTimer& gTimer);
		void updateWindowText(const char* _AppName);

		inline const void* getPlatform() const { return this->m_PlatState; };
		inline InputQueue& getInputQueue() { return this->m_InputQueue; };

		static void ConsolePrint(const char* message, u8 color);
		static void ConsolePrintError(const char* message, u8 color);

	private:
		InputQueue m_InputQueue;

		void* m_PlatState;

		const char* m_AppName;

		u32 m_XPos;
		u32 m_YPos;

		u32 m_Width;
		u32 m_Height;
	};
}

