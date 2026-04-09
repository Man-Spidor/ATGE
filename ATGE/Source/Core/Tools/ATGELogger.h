#pragma once

#include "Defines.h"

// #include <string>

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
		static const char* level_strings[6];
		static const u32 LogBuffSize = 512;

	public:
		static bool initLogging();
		static bool shutdown();

		static void reportAssertFailure(const char* condition, const char* msg, const char* file, u32 line);

	private:
		void privOut(LogLevel level);

	public:
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
			// TODO make this a proper singleton
			static Logger instance;
			return instance;
		}
#pragma warning( pop ) 

	private:
		char m_OutBuff[LogBuffSize];
		char m_Buff[LogBuffSize];
	};
}
