#pragma once

#include "PlatformInterface.h"

namespace ATGE
{
	class PrintAttorney
	{
		friend class Logger;

	public:
		static void ConsolePrint(const char* message, uchar color) { PlatformInterface::ConsolePrint(message, color); };
		static void ConsolePrintError(const char* message, uchar color) { PlatformInterface::ConsolePrintError(message, color); };
	};
}