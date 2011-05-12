#include <vortex/vtx_window.h>
#include <core/vtx_assertions.h>

#if defined(VTX_PLATFORM_WIN32)
#include <Windows.h>
#endif

#if defined(VTX_PLATFORM_LINUX)
#include <stdlib.h>
#endif

NativeWindow::NativeWindow(void)
{
}

NativeWindow *NativeWindow::create(WindowCreationParams &params)
{
		// Window does not exist and should be created.
	NativeWindow *window = new NativeWindow();
	if(params.windowHandle == 0)
	{
		window->manageWindow = true;
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
			style = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
			if(params.styleFlags & WindowCreationParams::STYLE_MENU)
				style |= WS_SYSMENU;
			if((params.styleFlags & WindowCreationParams::STYLE_NOCAPTION))
				style |= WS_CAPTION;
			if(params.styleFlags & WindowCreationParams::STYLE_MAXIMIZEBUTTON)
				style |= WS_MAXIMIZEBOX;
			if(params.styleFlags & WindowCreationParams::STYLE_MAXIMIZED)
				style |= WS_MAXIMIZE;
			if(params.styleFlags & WindowCreationParams::STYLE_SIZEABLE)
				style |= WS_SIZEBOX;
		}

		ATOM atom = RegisterClassEx(&wndclass);
		if(atom == 0)
		{
			int err = GetLastError();
			if(err != ERROR_CLASS_ALREADY_EXISTS)
				return 0;
		}

		window->handle = CreateWindow(
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
		if(window->handle == NULL)
		{
			int err = GetLastError();
		}
		ShowWindow(window->handle, SW_SHOW);
#elif defined(VTX_PLATFORM_LINUX) && defined(VTX_COMPILE_WITH_OPENGL) 
	// TODO: Need to create window without glX methods for software rendering.
	// When done, investigate if its usable for when compiling with OpenGL aswell. Unity is king.
	window->display = XOpenDisplay(getenv("DISPLAY"));
	int visualAttribs[12] = { GLX_RGBA, GLX_RED_SIZE, 1, GLX_GREEN_SIZE, 1, GLX_BLUE_SIZE, 1, GLX_DOUBLEBUFFER, GLX_DEPTH_SIZE, 1};
	XVisualInfo *visualInfo = glXChooseVisual(window->display, DefaultScreen(window->display), visualAttribs);	//TODO: Fix attributes!
	XSetWindowAttributes attribs;
	attribs.event_mask = ExposureMask | VisibilityChangeMask | KeyPressMask | PointerMotionMask | StructureNotifyMask;
	attribs.border_pixel = 0;
	attribs.bit_gravity = StaticGravity;
	attribs.colormap = XCreateColormap(
				window->display,
				RootWindow(window->display, visualInfo->screen),
				visualInfo->visual,
				AllocNone);
	unsigned long mask = CWBorderPixel | CWBitGravity | CWEventMask | CWColormap;

	window->win = XCreateWindow(
				window->display,
				DefaultRootWindow(window->display),
				params.windowPosition.x,
				params.windowPosition.y,
				params.windowSize.x,
				params.windowSize.y,
				0,					// Border width
				0,					// Depth (?)
				InputOutput,				// Class
				visualInfo->visual,
				mask,
				&attribs);
		
	XMapWindow(window->display, window->win);


	window->context = glXCreateContext(
				window->display,
				visualInfo,
				NULL,
				true);
	
#endif
	}
	// Window already exists.
	else
	{
		window->manageWindow = false;
	}
	ASSERT(window->handle != NULL);

return window;

}

void NativeWindow::destroy(void)
{
#if defined(VTX_PLATFORM_WIN32)
	HINSTANCE instance = GetModuleHandle(NULL);
	CloseWindow(this->handle);
	DestroyWindow(this->handle);
	UnregisterClass(__TEXT("VortexWin32"), instance);
#endif
#if defined(VTX_PLATFORM_LINUX)
	// TODO: Do it!
#endif
}

platform::WINDOW NativeWindow::getHandle(void)
{
	return this->handle;
}
