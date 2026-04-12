#pragma once

#include "ATGEngine.h"

namespace ATGE
{
	class ATGEAttorney
	{
		friend class TimeManager;
		friend class FreezeTime;

		static const float GetTimeInSeconds() { return ATGEngine::GetTimeInSeconds(); };
	};
}
