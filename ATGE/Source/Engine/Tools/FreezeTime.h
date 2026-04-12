#pragma once

#include "Engine/Input/InputTypes.h"

namespace ATGE
{
	class FreezeTime final
	{
		static const KEY s_FreezeKey = KEY::KEY_LEFT_BRACKET; ///< Key to toggle time freezing
		static const KEY s_SingleFrameKey = KEY::KEY_RIGHT_BRACKET; ///< Key to advance by single frame

		static const f32 s_DeadTimeThreshold; ///< Threshold for dead time
		static const f32 s_DefaultFrameTime; ///< Default frame time

	public:
		/// Default constructor.
		FreezeTime();
		/// Copy constructor is deleted to prevent unintended copying.
		FreezeTime(const FreezeTime& other) = delete;
		/// Copy assignment operator is deleted to prevent unintended copying.
		FreezeTime& operator=(const FreezeTime& other) = delete;
		/// Move constructor is deleted to prevent unintended moves.
		FreezeTime(FreezeTime&& other) = delete;
		/// Move assignment operator is deleted to prevent unintended moves.
		FreezeTime& operator=(FreezeTime&& other) = delete;
		/// Destructor.
		~FreezeTime() = default;

		/// Computes the game time considering time freezing.
		/// 
		/// This function calculates the current game time considering time freezing.
		/// 
		/// @param prevTime The previous game time before the update
		/// @return The current game time
		float computeGameTime(float prevTime);

	private:
		/// Checks if a key is released.
		bool hackedKeyRelease(KEY k);

		/// Tests for freeze keys.
		void testForFreezeKeys();

	private:
		f32 m_TotalFrozenTime; ///< Total frozen time
		b8 m_FreezeActive; ///< Flag indicating if time freezing is active
	};
}

