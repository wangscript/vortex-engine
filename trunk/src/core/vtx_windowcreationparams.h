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

#ifndef VTX_WINDOWCREATIONPARAMS_H
#define VTX_WINDOWCREATIONPARAMS_H

#include <core/vtx_atomic.h>
#include <core/vtx_vector2.h>

#include <string>

#if defined(VTX_PLATFORM_WIN32)
#define VWIN_USEDEFAULT		CW_USEDEFAULT
#endif
#if defined(VTX_PLATFORM_LINUX)
#define VWIN_USEDEFAULT		0xF0000000
#endif

namespace core
{

	class WindowCreationParams
	{
	public:
		WindowCreationParams();
		enum E_WINDOWSTYLE
		{
			STYLE_MAXIMIZED			= 1,
			STYLE_MAXIMIZEBUTTON	= 2,
			STYLE_NOCAPTION			= 4,
			STYLE_SIZEABLE			= 8,
			STYLE_MENU				= 16
		};
		bool isFullscreen;
		core::Vector2<core::U32_t> windowPosition;
		core::Vector2<core::U32_t> windowSize;
		std::string windowTitle;
		E_WINDOWSTYLE styleFlags;
		core::WINDOW windowHandle;
#if defined(VTX_PLATFORM_WIN32)
		WNDPROC wndProc;
#endif
#if defined(VTX_PLATFORM_LINUX)
		Display *displayX11;
#endif
	};

}

#endif