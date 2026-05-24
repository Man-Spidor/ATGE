#pragma once

#include "ATGELogger.h"

namespace ATGE
{
	class LoggerAttorney
	{
		friend class ATGEngine;

		static bool Initialize() { return Logger::Initialize(); };
		static bool Shutdown() { return Logger::Shutdown(); };
	};
}