#pragma once

#include "TimeManager.h"

namespace ATGE
{
	class TimeAttorney
	{
		friend class ATGEngine;
		static void ProcessTime() { TimeManager::ProcessTime(); };
		static void Initialize() { TimeManager::Initialize(); };
		static void Delete() { TimeManager::Delete(); };
	};
}