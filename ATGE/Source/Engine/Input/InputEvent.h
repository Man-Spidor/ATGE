#pragma once

#include "InputTypes.h"

namespace ATGE
{
	struct KeyInputEvent
	{
		KeyInputEvent() = default;
		KeyInputEvent(const KeyInputEvent& other) = default;
		KeyInputEvent& operator=(const KeyInputEvent& other) = default;
		KeyInputEvent(KeyInputEvent&& other) = default;
		KeyInputEvent& operator=(KeyInputEvent&& other) = default;
		~KeyInputEvent() = default;

		KeyInputEvent(KEY key, KeyEventType ket);

		KEY m_Key;
		KeyEventType m_EventType;
	};

	struct MouseInputEvent 
	{
	public:
		MouseInputEvent() = default;
		MouseInputEvent(const MouseInputEvent& other) = default;
		MouseInputEvent& operator=(const MouseInputEvent& other) = default;
		MouseInputEvent(MouseInputEvent&& other) = default;
		MouseInputEvent& operator=(MouseInputEvent&& other) = default;
		~MouseInputEvent() = default;


	};
}