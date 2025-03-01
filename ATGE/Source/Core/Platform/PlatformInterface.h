#pragma once

#include "Input/Mouse.h"
#include "Input/Keyboard.h"

namespace ATGE
{
	struct AppConfig
	{
		const char* appName = "AlmostTotalGameEngine";

		uint x = 0;
		uint y = 0;

		uint width = 800;
		uint height = 600;
	};

	class PlatformInterface
	{
		// Attorney for platform print functions
		friend class PrintAttorney;
				
	public:
		PlatformInterface() = default;
		PlatformInterface(const PlatformInterface& other) = default;
		PlatformInterface& operator=(const PlatformInterface& other) = default;
		PlatformInterface(PlatformInterface&& other) = default;
		PlatformInterface& operator=(PlatformInterface&& other) = default;
		~PlatformInterface() = default;

		bool initPlatform();
		bool initPlatform(const AppConfig& config);
		bool pumpMessages();
		void shutdown();
		
		inline const void* GetPlatform() const { return this->m_PlatState; };

	private:
		static void ConsolePrint(const char* message, uchar color);
		static void ConsolePrintError(const char* message, uchar color);

	private:
		Keyboard	m_Keyboard;
		Mouse		m_Mouse;

		void* m_PlatState;

		const char* m_AppName;

		uint m_XPos;
		uint m_YPos;

		uint m_Width;
		uint m_Height;		
	};
}
