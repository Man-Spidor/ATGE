#pragma once

#include "Defines.h"

namespace ATGE
{
#define ATGE_ENABLE_LOGGING

	static constexpr bool LogWarnEnabled = true;
	static constexpr bool LogInfoEnabled = true;
#ifdef _DEBUG
	static constexpr bool LogDebugEnabled = true;
	static constexpr bool LogTraceEnabled = true;
#else
	static constexpr bool LogDebugEnabled = false;
	static constexpr bool LogTraceEnabled = false;
#endif

	enum class LogLevel
	{
		LEVEL_FATAL = 0,
		LEVEL_ERROR = 1,
		LEVEL_WARN = 2,
		LEVEL_INFO = 3,
		LEVEL_DEBUG = 4,
		LEVEL_TRACE = 5
	};

	class Logger final
	{
		friend class LoggerAttorney;

	private:
		Logger();
		Logger(const Logger& other) = default;
		Logger& operator=(const Logger& other) = default;
		Logger(Logger&& other) = default;
		Logger& operator=(Logger&& other) = default;
		~Logger() = default;

		static const char* level_strings[6];
		static const u32 LogBuffSize = 512;

		static bool Initialize();
		static bool Shutdown();

		void privOut(LogLevel level);

	public:
		static void ReportAssertFailure(const char* condition, const char* msg, const char* file, u32 line);
		
		static void fatal(const char* const msg, ...);
		static void error(const char* const msg, ...);

#ifdef ATGE_ENABLE_LOGGING
	private:
		static void log(LogLevel level, const char* const msg, ...);

	public:
		static void warn(const char* const msg, ...);
		static void debug(const char* const msg, ...);
		static void trace(const char* const msg, ...);
		static void info(const char* const msg, ...);
#else
#pragma warning( push )
#pragma warning( disable : 4514 ) // unreferenced inline function has been removed
#pragma warning( disable : 4711 ) // unreferenced inline function has been removed		
		static void log(LogLevel level, const char* const msg, ...) { ATGE_UNUSED(level); ATGE_UNUSED(msg); };

		static void warn(const char* const msg, ...) { ATGE_UNUSED(msg); };
		static void debug(const char* const msg, ...) { ATGE_UNUSED(msg); };
		static void trace(const char* const msg, ...) { ATGE_UNUSED(msg); };
		static void info(const char* const msg, ...) { ATGE_UNUSED(msg); };
#pragma warning( pop ) 
#endif

#pragma warning( push )
#pragma warning( disable : 4514 ) // unreferenced inline function has been removed
		// #pragma warning( disable : 4711 ) // unreferenced inline function has been removed
	private:
		static Logger* s_Instance;
		static Logger& Instance()
		{
			// cant use an assert here, so just have to pray !
			return *s_Instance;
		}
#pragma warning( pop ) 

	private:
		char m_OutBuff[LogBuffSize];
		char m_Buff[LogBuffSize];
	};
}
