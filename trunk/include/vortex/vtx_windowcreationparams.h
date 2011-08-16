#ifndef VTX_WINDOWCREATIONPARAMS_H
#define VTX_WINDOWCREATIONPARAMS_H

#include <platform/vtx_atomic.h>
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
		std::wstring windowTitle;
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