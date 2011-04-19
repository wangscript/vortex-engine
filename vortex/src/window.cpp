#include "vtx_window.h"
#include "vtx_assertions.h"
#ifdef WIN32
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return 0;
}
#endif

void WindowManager::init(WindowCreationParams &params)
{
#ifdef WIN32
	HINSTANCE instance = GetModuleHandle(NULL);
	LPCWSTR className = __TEXT("VortexWin32");

	WNDCLASSEX wndclass;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW; //Redraw on horizontal or vertical movement or size changes.
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = instance;
	wndclass.hIcon = NULL; // TODO: Fix properly?
	wndclass.hbrBackground = NULL;
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = className;
	wndclass.hIconSm = NULL; // TODO: Fix properly?

	DWORD style;
	if(params.isFullscreen)
		style = WS_POPUP;
	else
	{
		style = WS_BORDER | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
		if(params.styleFlags & WindowCreationParams::STYLE_MENU != 0)
			style |= WS_SYSMENU;
		if(params.styleFlags & WindowCreationParams::STYLE_NOCAPTION == 0)
			style |= WS_CAPTION;
		if(params.styleFlags & WindowCreationParams::STYLE_MAXIMIZEBUTTON != 0)
			style |= WS_MAXIMIZEBOX;
		if(params.styleFlags & WindowCreationParams::STYLE_MAXIMIZED != 0)
			style |= WS_MAXIMIZE;
		if(params.styleFlags & WindowCreationParams::STYLE_SIZEABLE != 0)
			style |= WS_SIZEBOX;
	}

	RegisterClassEx(&wndclass);
	this->handle = CreateWindowEx(
		0,
		className,
		params.windowTitle.c_str(),
		style,
		params.windowPosition.x,
		params.windowPosition.y,
		params.windowSize.x,
		params.windowSize.y,
		NULL,
		NULL,
		instance,
		NULL);
	#endif

	ASSERT(this->handle != NULL);
}