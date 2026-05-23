#include "FreezeTime.h"
#include "ATGEAttorney.h"
#include "TimeManager.h"

namespace ATGE
{
	const float FreezeTime::s_DeadTimeThreshold = 0.1f;
	const float FreezeTime::s_DefaultFrameTime = 1.0f / 60.0f;

	FreezeTime::FreezeTime() :
		m_TotalFrozenTime(0.0f),
		m_FreezeActive(false)
	{
		ATGE_ASSERT(FreezeTime::s_DefaultFrameTime < FreezeTime::s_DeadTimeThreshold);
	}

	float FreezeTime::computeGameTime(float prevTime)
	{
        this->testForFreezeKeys(); // time may pass f freeze mode activated

        // Adjust real time to actual game time
        float currGameTime = ATGEAttorney::GetTimeInSeconds() - this->m_TotalFrozenTime;

        // test if any extra frozen time occurred since prev_gametime
        float frameTime = currGameTime - prevTime;
        if (frameTime > s_DeadTimeThreshold)
        {
            float extraFrozenTime = frameTime - s_DefaultFrameTime;

            this->m_TotalFrozenTime += extraFrozenTime; // new frozen time total
            currGameTime -= extraFrozenTime;   // adjust curr_gametime 

            Logger::trace("Current Game Time[%f]\n", currGameTime);
        }

        return currGameTime; // New current game time
	}

    bool FreezeTime::hackedKeyRelease(KEY k)
    {
        bool keyPressedAndReleased = false;

        if (InputManager::GetKeyState(k)) // Is the key pressed?
        {
            while (InputManager::GetKeyState(k))
            {
                MSG msg;
                GetMessage(&msg, NULL, 0, 0);
                TranslateMessage(&msg);
                DispatchMessage(&msg);

                InputManager::ProcessInputEvents();
            }

            keyPressedAndReleased = true; // k pressed and released.
        }
        return keyPressedAndReleased; // and k _must_ be released 
    }

    void FreezeTime::testForFreezeKeys()
    {
        if (hackedKeyRelease(s_FreezeKey) || this->m_FreezeActive)
        {
            Logger::trace("FREEZE FRAME at time %f (last frame: %f)\n", TimeManager::GetTime(), TimeManager::GetFrameTime());

            this->m_FreezeActive = true;  // Freeze mode active
            bool singleFrameRequest = false; // No single frame request

            while (this->m_FreezeActive && !singleFrameRequest)
            {
                if (hackedKeyRelease(s_FreezeKey))
                {
                    this->m_FreezeActive = false; // Cancel both freeze modes
                    singleFrameRequest = false;
                }
                else if (hackedKeyRelease(s_SingleFrameKey))
                {
                    singleFrameRequest = true; // Process a single frame
                }

                MSG msg;
                while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }

                InputManager::ProcessInputEvents();
            }
        }
    }
}