//Copyright (C) 2011 Emil Nordén
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either version 2
//of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

#include <core\vtx_assertions.h>
#include <platform\vtx_defineconfig.h>
#include <vortex\vtx_render.h>

#if defined(VTX_PLATFORM_WIN32)
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, message, wParam, lParam);
}
#endif

WindowCreationParams::WindowCreationParams()
{
	this->windowHandle = 0;
	this->isFullscreen = false;
	this->styleFlags = (WindowCreationParams::E_WINDOWSTYLE)0;
	this->windowPosition.x = VWIN_USEDEFAULT;
	this->windowPosition.y = VWIN_USEDEFAULT;
	this->windowSize.x = VWIN_USEDEFAULT;
	this->windowSize.y = VWIN_USEDEFAULT;
#if defined(VTX_PLATFORM_WIN32)
	this->wndProc = WndProc;
#endif
}
