#pragma once

namespace ATGE 
{
	struct WindowConfig;

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

		inline const void* GetPlatform() const { return this->m_PlatState; };

		static void ConsolePrint(const char* message, u8 color);
		static void ConsolePrintError(const char* message, u8 color);

	private:
		void* m_PlatState;

		const char* m_AppName;

		u32 m_XPos;
		u32 m_YPos;

		u32 m_Width;
		u32 m_Height;
	};
}

