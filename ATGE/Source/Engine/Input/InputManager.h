#pragma once

#include "InputTypes.h"

namespace ATGE
{
	class InputQueue;

	class InputManager final
	{
	public:
		InputManager() = delete;
		InputManager(const InputManager& other) = delete;
		InputManager& operator=(const InputManager& other) = delete;
		InputManager(InputManager&& other) = delete;
		InputManager& operator=(InputManager&& other) = delete;
		~InputManager() = default;

		InputManager(InputQueue& _inputQueue);
		
		static void Initialize(InputQueue& _inputQueue);

		static void ProcessInputEvents();

		static b8 GetKeyState(KEY key);

	private:
		void privProcessInputEvents();

	private:
		// TODO: Make this not a singleton :P		
		static InputManager* s_Instance;
		static InputManager& Instance()
		{
			ATGE_ASSERT(s_Instance);
			return *s_Instance;
		}

	private:
		b8 m_KeyStates[g_KeyStatesLength];

		InputQueue& m_InputQueueRef;
	};
}

