#pragma once

#include "InputManager.h"

namespace ATGE
{

	class InputAttorney
	{
		friend class PlatformInterface;
	public:
		static void SetKeyboard(const Keyboard* _pKeyboard) { InputManager::SetKeyboard(_pKeyboard); };
		static void SetMouse(const Mouse* _pMouse) { InputManager::SetMouse(_pMouse); };
	};
}
