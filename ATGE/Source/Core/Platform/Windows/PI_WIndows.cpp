#ifdef _WIN32

#include "Core/Platform/PlatformInterface.h"
#include "Core/Platform/Input/InputAttorney.h"
#include "Core/Platform/Input/Keyboard.h"
#include "Core/Platform/Input/Mouse.h"
#include "Core/Tools/ATGEAssert.h"
#include "WindowsHandles.h"

namespace ATGE
{
	LRESULT CALLBACK WindowProc(HWND hwnd, uint uMsg, WPARAM wParam, LPARAM lParam);
	Keyboard* wp_pKeyboardRef = nullptr;
	Mouse* wp_pMouseRef = nullptr;


	bool PlatformInterface::initPlatform()
	{
		AppConfig ac;
		return this->initPlatform(ac);
	}

	bool PlatformInterface::initPlatform(const AppConfig& config)
	{
		Logger::debug("Starting up windows app...\n");

		// Create and store our Windows-specific state.
		PS_WindowsState* state = new PS_WindowsState();
		this->m_PlatState = state;

		HRESULT result;

		// Get the application instance handle.
		state->h_instance = GetModuleHandle(nullptr);

		// Setup and register window class.
		HICON icon = LoadIcon(state->h_instance, IDI_APPLICATION);
		WNDCLASSA wc;
		memset(&wc, 0, sizeof(wc));
		wc.style = CS_DBLCLKS;  // Get double-clicks
		wc.lpfnWndProc = WindowProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = state->h_instance;
		wc.hIcon = icon;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);  // NULL; // Manage the cursor manually
		wc.hbrBackground = NULL;                   // Transparent
		wc.lpszClassName = "atge_window_class";

		result = RegisterClassA(&wc);
		ATGE_ASSERT_MSG(SUCCEEDED(result), "Window registration failed");

		// Create window
		int client_x = static_cast<int>(config.x);
		int client_y = static_cast<int>(config.y);
		int client_width = static_cast<int>(config.width);
		int client_height = static_cast<int>(config.height);

		int window_x = client_x;
		int window_y = client_y;
		int window_width = client_width;
		int window_height = client_height;

		DWORD window_style = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION;
		DWORD window_ex_style = WS_EX_APPWINDOW;

		window_style |= WS_MAXIMIZEBOX;
		window_style |= WS_MINIMIZEBOX;
		window_style |= WS_THICKFRAME;

		// Obtain the size of the border.
		RECT border_rect = { 0, 0, 0, 0 };
		AdjustWindowRectEx(&border_rect, window_style, 0, window_ex_style);

		// In this case, the border rectangle is negative.
		// window_x += border_rect.left;
		// window_y += border_rect.top;

		// Grow by the size of the OS border.
		window_width += border_rect.right - border_rect.left;
		window_height += border_rect.bottom - border_rect.top;

		HWND handle = CreateWindowExA(
			window_ex_style, "atge_window_class", config.appName,
			window_style, window_x, window_y, window_width, window_height,
			0, 0, state->h_instance, 0);

		ATGE_ASSERT_MSG(handle != 0, "Window creation failed!");

		state->hwnd = handle;

		// Show the window
		bool should_activate = true;  // TODO: if the window should not accept input, this should be false.
		int show_window_command_flags = should_activate ? SW_SHOW : SW_SHOWNOACTIVATE;
		// If initially minimized, use SW_MINIMIZE : SW_SHOWMINNOACTIVE;
		// If initially maximized, use SW_SHOWMAXIMIZED : SW_MAXIMIZE
		ShowWindow(state->hwnd, show_window_command_flags);

		// TODO Clock Setup (maybe)
		// Clock setup
		// LARGE_INTEGER frequency;
		// QueryPerformanceFrequency(&frequency);
		// clock_frequency = 1.0 / (f64)frequency.QuadPart;
		// QueryPerformanceCounter(&start_time);

		Logger::debug("Window succesfully created...\n");

		InputAttorney::SetKeyboard(&this->m_Keyboard);
		InputAttorney::SetMouse(&this->m_Mouse);

		wp_pKeyboardRef = &this->m_Keyboard;
		wp_pMouseRef = &this->m_Mouse;

		return true;
	}

	bool PlatformInterface::pumpMessages()
	{
		MSG msg;
		while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT)
				return false;

			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}

		return true;
	}

	void PlatformInterface::shutdown()
	{
		PS_WindowsState* state = (PS_WindowsState*)this->m_PlatState;

		Logger::debug("Closing window...\n");

		if (state->hwnd) {
			DestroyWindow(state->hwnd);
			state->hwnd = 0;
		}

		delete this->m_PlatState;
	}

	void PlatformInterface::ConsolePrint(const char* message, uchar color)
	{
		// FATAL,ERROR,WARN,INFO,DEBUG,TRACE
		static const uchar levels[6] = { 64, 4, 6, 2, 1, 8 };

		HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(console_handle, levels[color]);

		ulong length = strlen(message);
		LPDWORD number_written = 0;
		OutputDebugStringA(message);
		WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), message, (DWORD)length, number_written, 0);

		SetConsoleTextAttribute(console_handle, 7);
	}

	void PlatformInterface::ConsolePrintError(const char* message, uchar color)
	{
		// FATAL,ERROR,WARN,INFO,DEBUG,TRACE
		static const uchar levels[6] = { 64, 4, 6, 2, 1, 8 };

		HANDLE console_handle = GetStdHandle(STD_ERROR_HANDLE);
		SetConsoleTextAttribute(console_handle, levels[color]);

		ulong length = strlen(message);
		LPDWORD number_written = 0;
		OutputDebugStringA(message);
		WriteConsoleA(GetStdHandle(STD_ERROR_HANDLE), message, (DWORD)length, number_written, 0);

		// Display a Windows error message box with the same message.
		MessageBoxA(NULL, message, "Error", MB_OK | MB_ICONERROR);

		SetConsoleTextAttribute(console_handle, 7);

#ifdef _DEBUG
		// Trigger a breakpoint to let the developer inspect the error.
		DebugBreak();
#else
		// Terminate the program if no debugger is attached.
		exit(EXIT_FAILURE);
#endif
	}

	LRESULT WindowProc(HWND hwnd, uint uMsg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT result = 0;

		switch (uMsg) {
			// MOUSE MESSAGES
		case WM_KEYDOWN:
		{
			if (wParam == VK_ESCAPE) {
				DestroyWindow(hwnd);
				return 0;
			}

			const uchar key = static_cast<uchar>(wParam);

			Logger::debug("%c\n", key);

			wp_pKeyboardRef->onKeyPressed(key);
		}
		break;

		case WM_KEYUP:
		{
			const uchar key = static_cast<uchar>(wParam);
			wp_pKeyboardRef->onKeyReleased(key);
		}
		break;

		case WM_CHAR:
		{
			const uchar key = static_cast<uchar>(wParam);
			wp_pKeyboardRef->onChar(key);
		}
		break;

		// MOUSE MESSAGES
		case WM_MOUSEMOVE:
		{
			// int x = LOWORD(lParam);
			// int y = HIWORD(lParam);
			// this->m_Mouse.OnMouseMove(x, y);
		}
		break;

		case WM_LBUTTONDOWN:
		{
			// int x = LOWORD(lParam);
			// int y = HIWORD(lParam);
			// this->m_Mouse.OnLeftPressed(x, y);
		}
		break;

		case WM_RBUTTONDOWN:
		{
			// int x = LOWORD(lParam);
			// int y = HIWORD(lParam);
			// this->m_Mouse.OnRightPressed(x, y);
		}
		break;

		case WM_MBUTTONDOWN:
		{
			// int x = LOWORD(lParam);
			// int y = HIWORD(lParam);
			// this->m_Mouse.OnMiddlePressed(x, y);
		}
		break;

		case WM_LBUTTONUP:
		{
			// int x = LOWORD(lParam);
			// int y = HIWORD(lParam);
			// this->m_Mouse.OnLeftReleased(x, y);
		}
		break;

		case WM_RBUTTONUP:
		{
			// int x = LOWORD(lParam);
			// int y = HIWORD(lParam);
			// this->m_Mouse.OnRightReleased(x, y);
		}
		break;

		case WM_MBUTTONUP:
		{
			// int x = LOWORD(lParam);
			// int y = HIWORD(lParam);
			// this->m_Mouse.OnMiddleReleased(x, y);
		}
		break;

		case WM_MOUSEWHEEL:
		{
			// int x = LOWORD(lParam);
			// int y = HIWORD(lParam);
			// if (GET_WHEEL_DELTA_WPARAM(wParam) > 0) {
			// 	this->m_Mouse.OnWheelUp(x, y);
			// }
			// else if (GET_WHEEL_DELTA_WPARAM(wParam) < 0) {
			// 	this->m_Mouse.OnWheelDown(x, y);
			// }
		}
		break;

		case WM_INPUT:
		{
			// UINT dataSize;
			// GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, NULL, &dataSize, sizeof(RAWINPUTHEADER)); //Need to populate data size first
			//
			// if (dataSize > 0) {
			// 	std::unique_ptr<BYTE[]> raw_data = std::make_unique<BYTE[]>(dataSize);
			//
			// 	if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, raw_data.get(), &dataSize, sizeof(RAWINPUTHEADER)) == dataSize) {
			// 		RAWINPUT* raw = (RAWINPUT*)(raw_data.get());
			//
			// 		if (raw->header.dwType == RIM_TYPEMOUSE) {
			// 			// this->m_Mouse.OnMouseMoveRaw(raw->data.mouse.lLastX, raw->data.mouse.lLastY);
			// 		}
			// 	}
			// }
			//
			// result = DefWindowProc(hwnd, uMsg, wParam, lParam); //Need to call DefWindowProc for WM_INPUT messages
		}
		break;

		case WM_SETFOCUS:
			// Assume hWnd is the handle to your game window
			// RECT rect;
			// GetClientRect(this->m_WindowRenderer.GetHandle(), &rect);
			//
			// // Convert the client coordinates to screen coordinates
			// POINT ul; // Upper-left corner
			// ul.x = rect.left;
			// ul.y = rect.top;
			// ClientToScreen(this->m_WindowRenderer.GetHandle(), &ul);
			//
			// POINT lr; // Lower-right corner
			// lr.x = rect.right;
			// lr.y = rect.bottom;
			// ClientToScreen(this->m_WindowRenderer.GetHandle(), &lr);
			//
			// // Update the rect to screen coordinates
			// rect.left = ul.x;
			// rect.top = ul.y;
			// rect.right = lr.x;
			// rect.bottom = lr.y;
			//
			// // Confine the cursor
			// ClipCursor(&rect);
			break;

		case WM_KILLFOCUS:
			// Release the cursor
			ClipCursor(NULL);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		default:
			result = DefWindowProc(hwnd, uMsg, wParam, lParam);
			break;
		}

		return result;
	}
}

#endif