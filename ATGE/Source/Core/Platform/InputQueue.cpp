#include "InputQueue.h"

namespace ATGE
{
	void InputQueue::startQueues()
	{
		this->m_KeyEvents.createArray(g_KeyStatesLength);
	}
}
