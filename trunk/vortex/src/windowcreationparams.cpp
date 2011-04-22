#include "vtx_render.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, message, wParam, lParam);
}

WindowCreationParams::WindowCreationParams()
{
	this->windowHandle = 0;
	this->isFullscreen = false;
	this->windowPosition.x = VWIN_USEDEFAULT;
	this->windowPosition.y = VWIN_USEDEFAULT;
	this->windowSize.x = VWIN_USEDEFAULT;
	this->windowSize.y = VWIN_USEDEFAULT;
	this->wndProc = WndProc;
}