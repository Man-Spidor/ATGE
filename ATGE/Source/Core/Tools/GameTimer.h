//***************************************************************************************
// GameTimer.h by Frank Luna (C) 2011 All Rights Reserved.
//***************************************************************************************

#pragma once

namespace ATGE
{
	class GameTimer final
	{
	public:
		GameTimer();
		GameTimer(const GameTimer& other) = delete;
		GameTimer& operator=(const GameTimer& other) = delete;
		GameTimer(GameTimer&& other) = delete;
		GameTimer& operator=(GameTimer&& other) = delete;
		~GameTimer() = default;

		float TotalTime() const; // in seconds
		float DeltaTime() const; // in seconds

		void Reset(); // Call before message loop.
		void Start(); // Call when unpaused.
		void Stop();  // Call when paused.
		void Tick();  // Call every frame.

	private:
		f64 m_SecondsPerCount;
		f64 m_DeltaTime;

		i64 m_BaseTime;
		i64 m_PausedTime;
		i64 m_StopTime;
		i64 m_PrevTime;
		i64 m_CurrTime;

		b8 m_Stopped;
	};
}

