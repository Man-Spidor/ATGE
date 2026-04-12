#pragma once
#ifdef _WIN32

#include <windows.h>
#include <windowsx.h>  // param input extraction
#include <stdlib.h>

namespace ATGE
{
	class PS_WindowsState final
	{
	public:
		HINSTANCE h_instance = NULL;
		HWND hwnd = NULL;
	};
}

#endif