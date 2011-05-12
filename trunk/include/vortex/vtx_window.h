#ifndef VTX_WINDOW_H
#define VTX_WINDOW_H

#include <platform/vtx_defineconfig.h>
#include <platform/vtx_atomic.h>
#include <core/vtx_types.h>

#if defined(VTX_PLATFORM_LINUX)
#include <X11/Xlib.h>
#endif

#if defined(VTX_PLATFORM_LINUX) && defined(VTX_COMPILE_WITH_OPENGL)
#include <GL/glx.h>
#endif

#if defined(VTX_PLATFORM_WIN32)
#define VWIN_USEDEFAULT		CW_USEDEFAULT
#endif
#if defined(VTX_PLATFORM_LINUX)
#define VWIN_USEDEFAULT		0xF0000000
#endif

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
	core::Vector2<platform::U32> windowPosition;
	core::Vector2<platform::U32> windowSize;
	std::wstring windowTitle;
	E_WINDOWSTYLE styleFlags;
	platform::WINDOW windowHandle;
#if defined(VTX_PLATFORM_WIN32)
	WNDPROC wndProc;
#endif
};

class NativeWindow
{
private:
#if defined(VTX_PLATFORM_LINUX)
	Display *display;
	Window win;
#endif

#if defined(VTX_PLATFORM_LINUX) && defined(VTX_COMPILE_WITH_OPENGL)
	GLXContext context;
#endif
	platform::WINDOW handle;
	bool manageWindow;
	WindowCreationParams *params;
	NativeWindow(void);
public:
	void destroy(void);
	platform::WINDOW getHandle(void);
	static NativeWindow *create(WindowCreationParams &params);
};

#endif
