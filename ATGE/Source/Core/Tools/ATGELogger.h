#pragma once

#include "Defines.h"

#include <string>

namespace ATGE 
{	
#define ATGE_ENABLE_LOGGING

	static constexpr bool LogWarnEnabled = true;
	static constexpr bool LogInfoEnabled = true;
#ifdef _DEBUG
	static constexpr bool LogDebugEnabled = true;
	static constexpr bool LogTraceEnabled = true;
#else
	static constexpr bool LogDebugEnabled = true;
	static constexpr bool LogTraceEnabled = true;
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

	class Logger
	{
		static const char* level_strings[6];
		static const uint LogBuffSize = 256;

	public:
		static bool initLogging();
		static bool shutdown();

		static void reportAssertFailure(const char* condition, const char* msg, const char* file, uint line);

		static void log(LogLevel level, const std::string& msg);

		static void fatal(const char* const msg, ...);
		static void error(const char* const msg, ...);

#ifdef ATGE_ENABLE_LOGGING
		static void log(LogLevel level, const char* const msg, ...);

		static void warn(const char* const msg, ...);
		static void debug(const char* const msg, ...);
		static void trace(const char* const msg, ...);
#else
#pragma warning( push )
#pragma warning( disable : 4514 ) // unreferenced inline function has been removed
#pragma warning( disable : 4711 ) // unreferenced inline function has been removed		
		static void log(LogLevel level, const char* const msg, ...) { ATGE_UNUSED(level); ATGE_UNUSED(msg); };

		static void warn(const char* const msg, ...) { ATGE_UNUSED(msg); };
		static void debug(const char* const msg, ...) { ATGE_UNUSED(msg); };
		static void trace(const char* const msg, ...) { ATGE_UNUSED(msg); };
#pragma warning( pop ) 
#endif

	private:
#pragma warning( push )
#pragma warning( disable : 4514 ) // unreferenced inline function has been removed
#pragma warning( disable : 4711 ) // unreferenced inline function has been removed
		static Logger* s_instance;
		static Logger& Instance()
		{
			// TODO make this a proper singleton
			static Logger instance;
			return instance;
		}
#pragma warning( pop ) 

	private:
		char m_Buff[LogBuffSize];
	};
}
