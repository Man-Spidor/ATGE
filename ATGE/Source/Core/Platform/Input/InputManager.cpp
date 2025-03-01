#include "InputManager.h"

#include "Keyboard.h"


namespace ATGE
{
	const Keyboard* InputManager::s_pKeyboard = nullptr;
	const Mouse* InputManager::s_pMouse = nullptr;

	bool ATGE::InputManager::getKeyState(const char c)
	{
		return s_pKeyboard->getKeyState(c);
	}

	bool ATGE::InputManager::getKeyState(KEY key)
	{
		return s_pKeyboard->getKeyState(key);
	}
	void InputManager::SetKeyboard(const Keyboard* _pKeyboard)
	{
		s_pKeyboard = _pKeyboard;
	}
	void InputManager::SetMouse(const Mouse* _pMouse)
	{
		s_pMouse = _pMouse;
	}
}
