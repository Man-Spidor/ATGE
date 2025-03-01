#include "ATGEAssert.h"

#include "Core/Platform/PrintAttorney.h"

#include <cstdarg>

namespace ATGE 
{
	Logger* Logger::s_instance = nullptr;

	const char* Logger::level_strings[6] = {
		"[FATAL]: ",
		"[ERROR]: ",
		"[WARN]: ",
		"[INFO]: ",
		"[DEBUG]: ",
		"[TRACE]: "
	};

	bool Logger::initLogging()
	{
		// TODO: create log file :P

		s_instance = new Logger();

		return true;
	}
	bool Logger::shutdown()
	{
		// TODO: cleanup log file :P
		delete s_instance;
		return true;
	}

#pragma warning( push )
#pragma warning( disable : 4514 ) // unreferenced inline function has been removed
#pragma warning( disable: 4711 ) // function selected for automatic inline expansion
	void Logger::reportAssertFailure(const char* condition, const char* msg, const char* file, uint line)
	{
		log(LogLevel::LEVEL_FATAL, "Assertion Failure: %s, message: %s, in file: %s, line: %d\n", condition, msg, file, line);
	}

	void Logger::log(LogLevel level, const std::string& msg)
	{
		std::string outMsg = level_strings[(uint)level] + msg;

		if (level <= LogLevel::LEVEL_ERROR) 
			PrintAttorney::ConsolePrintError(outMsg.c_str(), static_cast<uchar>(level));		
		else
			PrintAttorney::ConsolePrint(outMsg.c_str(), static_cast<uchar>(level));
	}

	void Logger::fatal(const char* const msg, ...)
	{
		Logger& logger = Instance();

		std::string outMsg;

		va_list args;
		va_start(args, msg);

		vsprintf_s(&logger.m_Buff[0], LogBuffSize, msg, args);
		outMsg = logger.m_Buff;

		log(LogLevel::LEVEL_FATAL, outMsg);
	}

	void Logger::error(const char* const msg, ...)
	{
		Logger& logger = Instance();

		std::string outMsg;

		va_list args;
		va_start(args, msg);

		vsprintf_s(&logger.m_Buff[0], LogBuffSize, msg, args);
		outMsg = logger.m_Buff;

		log(LogLevel::LEVEL_ERROR, outMsg);
	}
#pragma warning( pop ) 

#ifdef ATGE_ENABLE_LOGGING

	void Logger::log(LogLevel level, const char* const msg, ...)
	{
		Logger& logger = Instance();
		
		std::string outMsg;

		va_list args;
		va_start(args, msg);

		vsprintf_s(&logger.m_Buff[0], LogBuffSize, msg, args);
		outMsg = logger.m_Buff;

		log(level, outMsg);
	}

	void Logger::warn(const char* const msg, ...)
	{
		Logger& logger = Instance();

		std::string outMsg;

		va_list args;
		va_start(args, msg);

		vsprintf_s(&logger.m_Buff[0], LogBuffSize, msg, args);
		outMsg = logger.m_Buff;

		log(LogLevel::LEVEL_WARN, outMsg);
	}

#ifdef _DEBUG
	void Logger::debug(const char* const msg, ...)
	{
		Logger& logger = Instance();

		std::string outMsg;

		va_list args;
		va_start(args, msg);

		vsprintf_s(&logger.m_Buff[0], LogBuffSize, msg, args);
		outMsg = logger.m_Buff;

		log(LogLevel::LEVEL_DEBUG, outMsg);
	}
#else
	void Logger::debug(const char* const msg, ...)
	{
		ATGE_UNUSED(msg);
	}

#endif

#ifdef _DEBUG
	void Logger::trace(const char* const msg, ...)
	{
		Logger& logger = Instance();

		std::string outMsg;

		va_list args;
		va_start(args, msg);

		vsprintf_s(&logger.m_Buff[0], LogBuffSize, msg, args);
		outMsg = logger.m_Buff;

		log(LogLevel::LEVEL_TRACE, outMsg);
	}
#else
	void Logger::trace(const char* const msg, ...)
	{
		ATGE_UNUSED(msg);
	}
#endif
#endif
}