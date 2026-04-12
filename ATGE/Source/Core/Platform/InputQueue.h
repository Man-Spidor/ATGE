#pragma once

#include "Engine/Input/InputEvent.h"
#include "DataStructures/SwapbackArray.h"

namespace ATGE
{
	class InputQueue
	{
	public:
		InputQueue() = default;
		InputQueue(const InputQueue& other) = default;
		InputQueue& operator=(const InputQueue& other) = default;
		InputQueue(InputQueue&& other) = default;
		InputQueue& operator=(InputQueue&& other) = default;
		~InputQueue() = default;

		void startQueues();

		inline void pushKeyEvent(KEY key, KeyEventType ket) { this->m_KeyEvents.emplace(key, ket); };
		// void pushMouseEvent(MOUSE mouse);

		inline SwapbackArray<KeyInputEvent>& getKeyQueue() { return this->m_KeyEvents; };

	private:
		SwapbackArray<KeyInputEvent> m_KeyEvents;
	};
}

