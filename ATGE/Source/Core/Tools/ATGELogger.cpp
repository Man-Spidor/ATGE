#include "ATGEAssert.h"

// #include "Core/Platform/PrintAttorney.h"
#include "Core/Platform/PlatformInterface.h"
#include "Core/Memory/MemoryManager.h"

#include <cstdarg>

namespace ATGE
{
	alignas(Logger) static char s_LoggerStorage[sizeof(Logger)];

	Logger* Logger::s_Instance = nullptr;

	const char* Logger::level_strings[6] = {
		"[FATAL]: ",
		"[ERROR]: ",
		"[WARN]: ",
		"[INFO]: ",
		"[DEBUG]: ",
		"[TRACE]: "
	};

	Logger::Logger() :
		m_Buff(),
		m_OutBuff()
	{
	}

	bool Logger::Initialize()
	{
		// TODO: create log file :P
#ifdef FRAMEWORK_H
		PLACEMENT_NEW_BEGIN
#undef new
			s_Instance = new(s_LoggerStorage) Logger();
		PLACEMENT_NEW_END
#else
		s_Instance = new(s_LoggerStorage) Logger();
#endif

		Logger::info("Logger Started Up!\n");

		return s_Instance != nullptr;
	}

	bool Logger::Shutdown()
	{
		// TODO: cleanup log file :P
		return true;
	}

#pragma warning( push )
#pragma warning( disable : 4514 ) // unreferenced inline function has been removed
#pragma warning( disable: 4711 ) // function selected for automatic inline expansion
	void Logger::ReportAssertFailure(const char* condition, const char* msg, const char* file, u32 line)
	{
		log(LogLevel::LEVEL_FATAL, "Assertion Failure: %s\n Message: %s\n In File: %s\n Line: %d\n", condition, msg, file, line);
	}

	void Logger::privOut(LogLevel level)
	{
		snprintf(this->m_OutBuff, LogBuffSize, "%s%s", level_strings[static_cast<u32>(level)], this->m_Buff);
		
		if (level <= LogLevel::LEVEL_ERROR)
			PlatformInterface::ConsolePrintError(this->m_OutBuff, static_cast<u8>(level));
		else
			PlatformInterface::ConsolePrint(this->m_OutBuff, static_cast<u8>(level));
	}

	void Logger::fatal(const char* const msg, ...)
	{
		Logger& logger = Instance();

		va_list args;
		va_start(args, msg);
		vsprintf_s(&logger.m_Buff[0], LogBuffSize, msg, args);
		va_end(args);

		Instance().privOut(LogLevel::LEVEL_FATAL);
	}

	void Logger::error(const char* const msg, ...)
	{
		Logger& logger = Instance();

		va_list args;
		va_start(args, msg);
		vsprintf_s(&logger.m_Buff[0], LogBuffSize, msg, args);
		va_end(args);

		Instance().privOut(LogLevel::LEVEL_ERROR);
	}
#pragma warning( pop ) 

#ifdef ATGE_ENABLE_LOGGING

	void Logger::log(LogLevel level, const char* const msg, ...)
	{
		Logger& logger = Instance();

		va_list args;
		va_start(args, msg);
		vsprintf_s(&logger.m_Buff[0], LogBuffSize, msg, args);
		va_end(args);

		Instance().privOut(level);
	}

	void Logger::warn(const char* const msg, ...)
	{
		Logger& logger = Instance();

		va_list args;
		va_start(args, msg);
		vsprintf_s(&logger.m_Buff[0], LogBuffSize, msg, args);
		va_end(args);

		Instance().privOut(LogLevel::LEVEL_WARN);
	}

#ifdef _DEBUG
	void Logger::info(const char* const msg, ...)
	{
		Logger& logger = Instance();

		va_list args;
		va_start(args, msg);
		vsprintf_s(&logger.m_Buff[0], LogBuffSize, msg, args);
		va_end(args);

		Instance().privOut(LogLevel::LEVEL_INFO);
	}

	void Logger::debug(const char* const msg, ...)
	{
		Logger& logger = Instance();

		va_list args;
		va_start(args, msg);
		vsprintf_s(&logger.m_Buff[0], LogBuffSize, msg, args);
		va_end(args);

		Instance().privOut(LogLevel::LEVEL_DEBUG);
	}

	void Logger::trace(const char* const msg, ...)
	{
		Logger& logger = Instance();

		va_list args;
		va_start(args, msg);
		vsprintf_s(&logger.m_Buff[0], LogBuffSize, msg, args);
		va_end(args);

		Instance().privOut(LogLevel::LEVEL_TRACE);
	}

#else
	void Logger::debug(const char* const msg, ...)
	{
		ATGE_UNUSED(msg);
	}

	void Logger::trace(const char* const msg, ...)
	{
		ATGE_UNUSED(msg);
	}

	void Logger::info(const char* const msg, ...)
	{
		ATGE_UNUSED(msg);
	}

#endif

#endif
}