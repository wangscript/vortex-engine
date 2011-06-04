#define ASSERTIONS_ENABLED

#include <vortex/vtx_window.h>
#include <core/vtx_assertions.h>
#include <vortex/vtx_vortex.h>

#if defined(VTX_PLATFORM_WIN32)
#include <Windows.h>
#endif

#if defined(VTX_PLATFORM_LINUX)
#include <stdlib.h>
#endif

std::map<platform::WINDOW, XErrorEvent*> *NativeWindow::lastErrorMap;
bool NativeWindow::isHandlingXErrors = false;

NativeWindow::NativeWindow(Root &parent) : VortexBase(parent)
{
#if defined(VTX_PLATFORM_LINUX)
	if(!NativeWindow::isHandlingXErrors)
	{
		NativeWindow::isHandlingXErrors = true;
		NativeWindow::lastErrorMap = new std::map<platform::WINDOW, XErrorEvent*>;
		XSetErrorHandler(NativeWindow::xErrorHandler);
	}
#endif
}

NativeWindow *NativeWindow::create(Root &parent, WindowCreationParams &params)
{
		// Window does not exist and should be created.
	NativeWindow *window = new NativeWindow(parent);
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
	XEvent event;
	// TODO: Need to create window without glX methods for software rendering.
	// When done, investigate if its usable for when compiling with OpenGL aswell. Unity is king.
	int result;
	window->display = XOpenDisplay(getenv("DISPLAY"));
	ASSERT(window->display != NULL);
	if(window->display == NULL)
	{
		std::wstring message(L"XOpenDisplay failed");
		parent.output->reportEvent(EventOutput::E_LEVEL_FATAL, message);
	}

	int visualAttribs[12] = { GLX_RGBA, GLX_RED_SIZE, 1, GLX_GREEN_SIZE, 1, GLX_BLUE_SIZE, 1, GLX_DOUBLEBUFFER, GLX_DEPTH_SIZE, 1};
	XVisualInfo *visualInfo = glXChooseVisual(window->display, DefaultScreen(window->display), visualAttribs);	//TODO: Fix attributes!
	ASSERT(visualInfo != NULL);
	if(visualInfo == NULL)
	{
		std::wstring message(L"glXChooseVisual failed");
		parent.output->reportEvent(EventOutput::E_LEVEL_FATAL, message);
	}
	XSetWindowAttributes attribs;
	attribs.event_mask = ExposureMask | VisibilityChangeMask | KeyPressMask | PointerMotionMask | StructureNotifyMask;
	attribs.border_pixel = 0;
	attribs.bit_gravity = StaticGravity;
	attribs.colormap = XCreateColormap(
				window->display,
				RootWindow(window->display, visualInfo->screen),
				visualInfo->visual,
				AllocNone);
	ASSERT(attribs.colormap != BadAlloc);
	ASSERT(attribs.colormap != BadMatch);
	ASSERT(attribs.colormap != BadValue);
	ASSERT(attribs.colormap != BadWindow);
	if(	BadAlloc == attribs.colormap ||
		BadMatch == attribs.colormap ||
		BadValue == attribs.colormap ||
		BadWindow == attribs.colormap)
	{
		std::wstring message(L"XCreateColormap");
		parent.output->reportMethodFailedEvent(EventOutput::E_LEVEL_FATAL, message, attribs.colormap);
	}


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
	ASSERT(window->win != BadAlloc);
	ASSERT(window->win != BadColor);
	ASSERT(window->win != BadCursor);
	ASSERT(window->win != BadMatch);
	ASSERT(window->win != BadPixmap);
	ASSERT(window->win != BadValue);
	ASSERT(window->win != BadWindow);
	if(	window->win == BadAlloc  ||
		window->win == BadColor  ||	
		window->win == BadCursor ||
		window->win == BadMatch  ||
		window->win == BadPixmap ||
		window->win == BadValue  ||
		window->win == BadWindow)
	{
		std::wstring message(L"XCreateWindow");
		parent.output->reportMethodFailedEvent(EventOutput::E_LEVEL_FATAL, message, window->win);
	}


	// TODO: Find out a better way to get a char* from a wstring.
	std::string title(params.windowTitle.begin(), params.windowTitle.end());
	title.assign(params.windowTitle.begin(), params.windowTitle.end());
	result = XStoreName(window->display, window->win, title.c_str());
	ASSERT(result != BadAlloc);
	ASSERT(result != BadWindow);
	if(BadAlloc == result || BadWindow == result)
	{
		std::wstring message(L"XStoreName");
		parent.output->reportMethodFailedEvent(EventOutput::E_LEVEL_FATAL, message, result);
	}
		
	result = XMapWindow(window->display, window->win);
	ASSERT(result != BadWindow);
	if(BadWindow == result)
	{
		std::wstring message(L"XMapWindow failed with BadWindow");
		parent.output->reportEvent(EventOutput::E_LEVEL_FATAL, message);
	}

	window->context = glXCreateContext(
				window->display,
				visualInfo,
				NULL,
				true);
	ASSERT(window->context != NULL);
	if(window->context == NULL)
	{
		XErrorEvent *event = NativeWindow::getLastXError(window->win);
		std::wstring message(L"glXCreateContext");
		parent.output->reportMethodFailedEvent(EventOutput::E_LEVEL_FATAL, message, event->error_code);
	}
#endif
	}
	// Window already exists.
	else
	{
		window->handle = params.windowHandle;
		window->manageWindow = false;
                window->win = window->handle;

		window->display = XOpenDisplay(getenv("DISPLAY"));
		ASSERT(window->display != NULL);
		if(window->display == NULL)
		{
			std::wstring message(L"XOpenDisplay failed");
			parent.output->reportEvent(EventOutput::E_LEVEL_FATAL, message);
		}

		int visualAttribs[12] = { GLX_RGBA, GLX_RED_SIZE, 1, GLX_GREEN_SIZE, 1, GLX_BLUE_SIZE, 1, GLX_DOUBLEBUFFER, GLX_DEPTH_SIZE, 1};
		XVisualInfo *visualInfo = glXChooseVisual(window->display, DefaultScreen(window->display), visualAttribs);	//TODO: Fix attributes!
		ASSERT(visualInfo != NULL);
		if(visualInfo == NULL)
		{
			std::wstring message(L"glXChooseVisual failed");
			parent.output->reportEvent(EventOutput::E_LEVEL_FATAL, message);
		}


		window->context = glXCreateContext(
				window->display,
				visualInfo,
				NULL,
				true);
		ASSERT(window->context != NULL);
		if(window->context == NULL)
		{
			XErrorEvent *event = NativeWindow::getLastXError(window->win);
			std::wstring message(L"glXCreateContext");
			parent.output->reportMethodFailedEvent(EventOutput::E_LEVEL_FATAL, message, event->error_code);
		}
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

XErrorEvent *NativeWindow::getLastXError(platform::WINDOW handle)
{
	std::map<platform::WINDOW, XErrorEvent*>::iterator it;
	XErrorEvent *lastError = NULL;
	
	it = NativeWindow::lastErrorMap->find(handle);
	if(it != NativeWindow::lastErrorMap->end())
	{
		lastError = it->second;
	}
	return lastError;
}

int NativeWindow::xErrorHandler(Display *display, XErrorEvent *event)
{
	NativeWindow::lastErrorMap[0][event->resourceid] = event;
	return 0;
}
