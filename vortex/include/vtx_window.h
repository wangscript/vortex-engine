#ifndef VTX_WINDOW_H
#define VTX_WINDOW_H

#include "vtx_types.h"
#include "vtx_atomic.h"

class WindowCreationParams
{
public:
	//WindowCreationParams(
	enum E_WINDOWSTYLE
	{
		STYLE_MAXIMIZED			= 1,
		STYLE_MAXIMIZEBUTTON	= 2,
		STYLE_NOCAPTION			= 4,
		STYLE_SIZEABLE			= 8,
		STYLE_MENU				= 16
	};
	bool isFullscreen;
	core::Vector2<U32> windowPosition;
	core::Vector2<U32> windowSize;
	std::wstring windowTitle;
	E_WINDOWSTYLE styleFlags;
};

class WindowManager
{
private:
#ifdef WIN32
	HWND handle;
#endif
public:
	void init(WindowCreationParams& params);
	void destory(void);
};

#endif