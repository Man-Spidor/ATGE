#include "GameTimer.h"

namespace ATGE
{
	GameTimer::GameTimer() : 
		m_SecondsPerCount(0.0),
		m_DeltaTime(-1.0), 
		m_BaseTime(0),
		m_PausedTime(0),
		m_StopTime(0),
		m_PrevTime(0),
		m_CurrTime(0), 
		m_Stopped(false)
	{
		i64 countsPerSec;
		QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
		this->m_SecondsPerCount = 1.0 / (f64)countsPerSec;
	}

	// Returns the total time elapsed since Reset() was called, NOT counting any
	// time when the clock is stopped.
	float GameTimer::TotalTime()const
	{
		// If we are stopped, do not count the time that has passed since we stopped.
		// Moreover, if we previously already had a pause, the distance 
		// this->m_StopTime - this->m_BaseTime includes paused time, which we do not want to count.
		// To correct this, we can subtract the paused time from this->m_StopTime:  
		//
		//                     |<--paused time-->|
		// ----*---------------*-----------------*------------*------------*------> time
		//  this->m_BaseTime       this->m_StopTime        startTime     this->m_StopTime    this->m_CurrTime

		if (this->m_Stopped)
		{
			return (float)(((this->m_StopTime - this->m_PausedTime) - this->m_BaseTime) * this->m_SecondsPerCount);
		}

		// The distance this->m_CurrTime - this->m_BaseTime includes paused time,
		// which we do not want to count.  To correct this, we can subtract 
		// the paused time from this->m_CurrTime:  
		//
		//  (this->m_CurrTime - this->m_PausedTime) - this->m_BaseTime 
		//
		//                     |<--paused time-->|
		// ----*---------------*-----------------*------------*------> time
		//  this->m_BaseTime       this->m_StopTime        startTime     this->m_CurrTime

		else
		{
			return (float)(((this->m_CurrTime - this->m_PausedTime) - this->m_BaseTime) * this->m_SecondsPerCount);
		}
	}

	float GameTimer::DeltaTime()const
	{
		return (float)this->m_DeltaTime;
	}

	void GameTimer::Reset()
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		this->m_BaseTime = currTime;
		this->m_PrevTime = currTime;
		this->m_StopTime = 0;
		this->m_Stopped = false;
	}

	void GameTimer::Start()
	{
		__int64 startTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&startTime);


		// Accumulate the time elapsed between stop and start pairs.
		//
		//                     |<-------d------->|
		// ----*---------------*-----------------*------------> time
		//  this->m_BaseTime       this->m_StopTime        startTime     

		if (this->m_Stopped)
		{
			this->m_PausedTime += (startTime - this->m_StopTime);

			this->m_PrevTime = startTime;
			this->m_StopTime = 0;
			this->m_Stopped = false;
		}
	}

	void GameTimer::Stop()
	{
		if (!this->m_Stopped)
		{
			__int64 currTime;
			QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

			this->m_StopTime = currTime;
			this->m_Stopped = true;
		}
	}

	void GameTimer::Tick()
	{
		if (this->m_Stopped)
		{
			this->m_DeltaTime = 0.0;
			return;
		}

		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
		this->m_CurrTime = currTime;

		// Time difference between this frame and the previous.
		this->m_DeltaTime = (this->m_CurrTime - this->m_PrevTime) * this->m_SecondsPerCount;

		// Prepare for next frame.
		this->m_PrevTime = this->m_CurrTime;

		// Force nonnegative.  The DXSDK's CDXUTTimer mentions that if the 
		// processor goes into a power save mode or we get shuffled to another
		// processor, then this->m_DeltaTime can be negative.
		if (this->m_DeltaTime < 0.0)
		{
			this->m_DeltaTime = 0.0;
		}
	}


}