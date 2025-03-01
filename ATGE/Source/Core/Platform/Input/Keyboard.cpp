#include "Keyboard.h"

namespace ATGE
{
	void Keyboard::onKeyPressed(const uchar key)
	{
		this->m_KeyStates[key] = true;

		// TODO: Add listener functionality
	}

	void Keyboard::onKeyReleased(const uchar key)
	{
		this->m_KeyStates[key] = false;

		// TODO: Add listener functionality
	}

	void Keyboard::onChar(const uchar key)
	{
		// TODO: implement char buffer
		// this->m_CharBuffer.push(key);
		ATGE_UNUSED(key);
	}

	uchar Keyboard::readChar()
	{
		if (!this->m_CharBuffer.empty()) {
			uchar e = this->m_CharBuffer.front();	// Get first char from queue
			this->m_CharBuffer.pop();				// Remove first char from queue
			return e;								// Returns char
		}

		return 0;
	}

	bool Keyboard::getKeyState(const char c) const
	{
		return this->m_KeyStates[static_cast<uint>(c)];
	}

	bool Keyboard::getKeyState(KEY key) const
	{
		return this->m_KeyStates[static_cast<uint>(key)];
	}
}
