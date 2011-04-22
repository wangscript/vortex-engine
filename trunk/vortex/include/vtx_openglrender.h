#ifndef VTX_OPENGLRENDER_H
#define VTX_OPENGLRENDER_H

#include "vtx_renderinternal.h"
#include "vtx_render.h"

class OpenGLRender : public RenderAPI
{
private:
	platform::WINDOW windowHandle;
#if defined(VTX_PLATFORM_WIN32)
	HDC hDC;
	HGLRC renderContext;
#endif
public:
	OpenGLRender(RenderCreationParams &params, platform::WINDOW outputWindow);
	~OpenGLRender(void);
	virtual void swap(void);
	virtual void clear(void);
};

#endif