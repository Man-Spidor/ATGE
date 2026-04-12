#include "InputManager.h"

#include "Core/Memory/MemoryManager.h"
#include "core/Platform/InputQueue.h"

namespace ATGE
{
	InputManager* InputManager::s_Instance = nullptr;

	b8 InputManager::GetKeyState(KEY key)
	{
		return Instance().m_KeyStates[static_cast<u32>(key)];
	}

	void InputManager::privProcessInputEvents()
	{
		auto& keyEvents = this->m_InputQueueRef.getKeyQueue();
		
		while(!keyEvents.empty()) {
			auto& kE = keyEvents.pop();

			switch (kE.m_EventType)
			{
			case KeyEventType::KEY_PRESSED:
				Logger::info("%c Key Pressed!\n", static_cast<u8>(kE.m_Key));
				this->m_KeyStates[static_cast<u32>(kE.m_Key)] = true;
				break;

			case KeyEventType::KEY_RELEASED:
				Logger::info("%c Key Released!\n", static_cast<u8>(kE.m_Key));
				this->m_KeyStates[static_cast<u32>(kE.m_Key)] = false;
				break;
			default:
				break;
			}
		}
	}

	InputManager::InputManager(InputQueue& _inputQueue) :
		m_KeyStates(),
		m_InputQueueRef(_inputQueue)
	{
	}

	void InputManager::Initialize(InputQueue& _inputQueue)
	{
		s_Instance = MemoryManager::allocate<InputManager>(1, _inputQueue);
	}

	void InputManager::processInputEvents()
	{
		Instance().privProcessInputEvents();
	}
}
