#pragma once

#include "InputTypes.h"

namespace ATGE
{
	class Mouse;
	class Keyboard;

	/// Class that acts as pass through for all simple input queries
	class InputManager
	{
		friend class InputAttorney;

	private:
		InputManager() = delete;
		InputManager(const InputManager& other) = delete;
		InputManager& operator=(const InputManager& other) = delete;
		InputManager(InputManager&& other) = delete;
		InputManager& operator=(InputManager&& other) = delete;
		~InputManager() = default;
	
		static void SetKeyboard(const Keyboard* _Keyboard);
		static void SetMouse(const Mouse* _pMouse);

	public:
		/// @brief Get the state of a specific key.
		/// @param c The character representing the key.
		/// @return True if the key is pressed, false otherwise.
		static bool getKeyState(const char c);

		/// @brief Get the state of a specific key.
		/// @param key The key code.
		/// @return True if the key is pressed, false otherwise.
		static bool getKeyState(KEY key);

	private:
		static const Keyboard* s_pKeyboard;
		static const Mouse* s_pMouse;
	};
}
