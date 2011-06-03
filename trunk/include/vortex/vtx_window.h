#ifndef VTX_WINDOW_H
#define VTX_WINDOW_H

#include <platform/vtx_defineconfig.h>
#include <platform/vtx_atomic.h>
#include <core/vtx_types.h>
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

class NativeWindow : VortexBase
{
private:
	platform::WINDOW handle;
	bool manageWindow;
	WindowCreationParams *params;
	NativeWindow(Root &parent);
public:
	void destroy(void);
	platform::WINDOW getHandle(void);
	static NativeWindow *create(Root &parent, WindowCreationParams &params);

#if defined(VTX_PLATFORM_LINUX)
	Display *display;
	Window win;

	// X Error handling
	static bool isHandlingXErrors;
	static XErrorEvent *getLastXError(platform::WINDOW);
	static std::map<platform::WINDOW, XErrorEvent*> *lastErrorMap;
	static int xErrorHandler(Display*, XErrorEvent*);
#endif

#if defined(VTX_PLATFORM_LINUX) && defined(VTX_COMPILE_WITH_OPENGL)
	GLXContext context;
#endif
};

#endif
