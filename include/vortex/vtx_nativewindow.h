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

#ifndef VTX_NATIVEWINDOW_H
#define VTX_NATIVEWINDOW_H

#include <platform/vtx_buildconfig.h>
#include <platform/vtx_atomic.h>
#include <vortex/vtx_vortexbase.h>

#if defined(VTX_PLATFORM_LINUX)
#include <X11/Xlib.h>
#include <map>
#endif

#if defined(VTX_PLATFORM_LINUX) && defined(VTX_COMPILE_WITH_OPENGL)
#include <GL/glx.h>
#include <X11/Xmd.h>
#include <GL/glxproto.h>
#endif

namespace core
{

	class WindowCreationParams;

	class NativeWindow : VortexBase
	{
	private:
		core::WINDOW handle;
		bool manageWindow;
		core::WindowCreationParams *params;
		NativeWindow(Root &parent);
	public:
		void destroy(void);
		core::WINDOW getHandle(void);
		static NativeWindow *create(core::Root &parent, core::WindowCreationParams &params);

#if defined(VTX_PLATFORM_LINUX)
		Display *display;
		Window win;

		// X Error handling
		static bool isHandlingXErrors;
		static XErrorEvent *getLastXError(core::WINDOW);
		static std::map<platform::WINDOW, XErrorEvent*> *lastErrorMap;
		static int xErrorHandler(Display*, XErrorEvent*);
#endif

#if defined(VTX_PLATFORM_LINUX) && defined(VTX_COMPILE_WITH_OPENGL)
		GLXContext context;
#endif
	};

}

#endif
