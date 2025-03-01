#pragma once

#include "InputTypes.h"
#include "InputDevice.h"

#include <array>
#include <queue>

namespace ATGE
{
	class Keyboard : public InputDevice
	{
	public:
		Keyboard() = default;
		Keyboard(const Keyboard& other) = default;
		Keyboard& operator=(const Keyboard& other) = default;
		Keyboard(Keyboard&& other) = default;
		Keyboard& operator=(Keyboard&& other) = default;
		~Keyboard() = default;

		/// @brief Handle key press events.
		/// @param key The key code.
		void onKeyPressed(const uchar key);

		/// @brief Handle key release events.
		/// @param key The key code.
		void onKeyReleased(const uchar key);

		/// @brief Handle character input events.
		/// @param key The character code.
		void onChar(const uchar key);

		/// @brief Read the next character from the buffer.
		/// @return The next character.
		uchar readChar();

		/// @brief Get the state of a specific key.
		/// @param c The character representing the key.
		/// @return True if the key is pressed, false otherwise.
		bool getKeyState(const char c) const;

		/// @brief Get the state of a specific key.
		/// @param key The key code.
		/// @return True if the key is pressed, false otherwise.
		bool getKeyState(KEY key) const;

	private:
		std::array<bool, KeyStatesLength> m_KeyStates; ///< Array to store the state of each key.
		std::queue<uchar> m_CharBuffer;
	};
}