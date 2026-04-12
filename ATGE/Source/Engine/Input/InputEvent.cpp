#include "InputEvent.h"

namespace ATGE
{
	KeyInputEvent::KeyInputEvent(KEY key, KeyEventType ket) :
		m_Key(key),
		m_EventType(ket)
	{
	}
}
