#include "TimeManager.h"

#include "Core/Memory/MemoryManager.h"

namespace ATGE
{
	TimeManager* TimeManager::s_Instance = nullptr;
	float TimeManager::s_PrevTime;
	float TimeManager::s_CurrTime;
	float TimeManager::s_FrameTime;

	FreezeTime TimeManager::timeFreeze;

	void TimeManager::ProcessTime()
	{
		s_PrevTime = s_CurrTime;

		// s_CurrTime = MOABEAttorney::GetTimeInSeconds();
		s_CurrTime = timeFreeze.computeGameTime(s_PrevTime);

		s_FrameTime = s_CurrTime - s_PrevTime;
	}

	void TimeManager::Initialize()
	{
		ATGE_ASSERT(!s_Instance);
		s_Instance = MemoryManager::allocate<TimeManager>();
	}

	void TimeManager::Delete()
	{
		// nothing ?
	}

	const float TimeManager::GetTime()
	{
		return Instance().s_CurrTime;
	}

	const float TimeManager::GetFrameTime()
	{
		return Instance().s_FrameTime;
	}
}