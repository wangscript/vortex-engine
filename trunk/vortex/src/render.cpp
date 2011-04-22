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

#include "vtx_render.h"
#if defined(VTX_COMPILE_WITH_DX10)
#include "vtx_dx10render.h"
#endif
#if defined(VTX_COMPILE_WITH_OPENGL)
#include "vtx_openglrender.h"
#endif

#include "vtx_assertions.h"
#ifdef WIN32
#include <Windows.h>
#endif

using namespace platform;

RenderManager::RenderManager(void)
{
}

void RenderManager::init(RenderCreationParams &params, WindowCreationParams &windowParams)
{
	this->createWindow(windowParams);
	if(params.rapi == E_RAPI_DX10)
	{
		this->render = new DX10Render(params, this->windowHandle);
	}
	else if(params.rapi == E_RAPI_OPENGL)
	{
		this->render = new OpenGLRender(params, this->windowHandle);
	}
}

void RenderManager::destroy(void)
{
	if(this->manageWindow)
	{
#if defined(VTX_PLATFORM_WIN32)
		CloseWindow(this->windowHandle);
		DestroyWindow(this->windowHandle);
#endif
	}
}

RenderAPI *RenderManager::getRenderObject(void)
{
	return this->render;
}

platform::WINDOW RenderManager::getWindowHandle(void)
{
	return this->windowHandle;
}

void RenderManager::createWindow(WindowCreationParams &params)
{
		// Window does not exist and should be created.
	if(params.windowHandle == 0)
	{
		this->manageWindow = true;
#if defined(VTX_PLATFORM_WIN32)
		HINSTANCE instance = GetModuleHandle(NULL);
		LPCWSTR className = __TEXT("VortexWin32");

		WNDCLASSEX wndclass;
		wndclass.cbSize = sizeof(WNDCLASSEX);
		wndclass.style = CS_OWNDC; // CS_HREDRAW | CS_VREDRAW; //Redraw on horizontal or vertical movement or size changes.
		wndclass.lpfnWndProc = params.wndProc;
		wndclass.cbClsExtra = 0;
		wndclass.cbWndExtra = 0;
		wndclass.hInstance = instance;
		wndclass.hIcon = NULL; // TODO: Fix properly?
		wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
		wndclass.lpszMenuName = NULL;
		wndclass.lpszClassName = className;
		wndclass.hIconSm = NULL; // TODO: Fix properly?

		DWORD style;
		if(params.isFullscreen)
			style = WS_POPUP;
		else
		{
			style = WS_BORDER | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
			if(params.styleFlags & WindowCreationParams::STYLE_MENU)
				style |= WS_SYSMENU;
			if(~(params.styleFlags & WindowCreationParams::STYLE_NOCAPTION))
				style |= WS_CAPTION;
			if(params.styleFlags & WindowCreationParams::STYLE_MAXIMIZEBUTTON)
				style |= WS_MAXIMIZEBOX;
			if(params.styleFlags & WindowCreationParams::STYLE_MAXIMIZED)
				style |= WS_MAXIMIZE;
			if(params.styleFlags & WindowCreationParams::STYLE_SIZEABLE)
				style |= WS_SIZEBOX;
		}

		ATOM a = RegisterClassEx(&wndclass);
		if(a == 0)
		{
			int err = GetLastError();
		}

		this->windowHandle = CreateWindow(
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
		if(this->windowHandle == NULL)
		{
			int err = GetLastError();
		}
#endif
	}
	// Window already exists.
	else
	{
		this->manageWindow = false;
	}
	ASSERT(this->windowHandle != NULL);
	
	ShowWindow(this->windowHandle, SW_SHOW);

}