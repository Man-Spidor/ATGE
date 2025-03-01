#pragma once
namespace ATGE
{
	class Mouse
	{
	public:
		Mouse() = default;
		Mouse(const Mouse& other) = default;
		Mouse& operator=(const Mouse& other) = default;
		Mouse(Mouse&& other) = default;
		Mouse& operator=(Mouse&& other) = default;
		~Mouse() = default;

		// WINDOW PROC FUNCTIONS
		// void OnLeftPressed(int x, int y);
		// void OnLeftReleased(int x, int y);
		// void OnRightPressed(int x, int y);
		// void OnRightReleased(int x, int y);
		// void OnMiddlePressed(int x, int y);
		// void OnMiddleReleased(int x, int y);
		// void OnWheelUp(int x, int y);
		// void OnWheelDown(int x, int y);
		// void OnMouseMove(int x, int y);
		// void OnMouseMoveRaw(int x, int y);



	private:

	};
}

