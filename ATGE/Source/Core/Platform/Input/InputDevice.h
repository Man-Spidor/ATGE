#pragma once

class InputEvent;
class InputCallback;

class InputDevice
{
public:
	InputDevice() = default;
	InputDevice(const InputDevice& other) = default;
	InputDevice& operator=(const InputDevice& other) = default;
	InputDevice(InputDevice&& other) = default;
	InputDevice& operator=(InputDevice&& other) = default;
	~InputDevice() = default;

	void registerInput(InputEvent* ie, InputCallback* iCB);
	void deregisterInput(InputEvent* ie, InputCallback* iCB);

};

