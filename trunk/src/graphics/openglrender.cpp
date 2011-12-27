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

// TODO: REMOVE THIS and implement OpenGl for linux

#if defined(VTX_PLATFORM_LINUX)
#include <GL/glx.h>
#endif

#include <core/vtx_buildconfig.h>
#include <graphics/vtx_openglrender.h>
#include <GL/gl.h>
#if defined(VTX_PLATFORM_LINUX)
//#include <GL/glxproto.h>
#endif
#include <core/vtx_vortex.h>
#include <core/vtx_nativewindow.h>
#include <core/vtx_eventoutput.h>

graphics::OpenGLRender::OpenGLRender(graphics::RenderCreationParams &params, core::NativeWindow *outputWindow)
{
	this->window = outputWindow;
#if defined(VTX_PLATFORM_WIN32)
	this->hDC = GetDC(outputWindow->getHandle());
	BOOL b;
	PIXELFORMATDESCRIPTOR pixelDesc = {
                sizeof(PIXELFORMATDESCRIPTOR),          //size of structure
                1,                                      //default version
                PFD_DRAW_TO_WINDOW |                    //window drawing support
                PFD_SUPPORT_OPENGL |                    //opengl support
                PFD_DOUBLEBUFFER,                       //double buffering support
                PFD_TYPE_RGBA,                          //RGBA color mode
                32,                                     //32 bit color mode
                0, 0, 0, 0, 0, 0,                       //ignore color bits
                0,                                      //no alpha buffer
                0,                                      //ignore shift bit
                0,                                      //no accumulation buffer
                0, 0, 0, 0,                             //ignore accumulation bits
                16,                                     //16 bit z-buffer size
                0,                                      //no stencil buffer
                0,                                      //no aux buffer
                PFD_MAIN_PLANE,                         //main drawing plane
                0,                                      //reserved
                0, 0, 0 };                              //layer masks ignored
	int pixelFormat = ChoosePixelFormat(this->hDC, &pixelDesc);
	b = SetPixelFormat(this->hDC, pixelFormat, &pixelDesc); 

	DescribePixelFormat(this->hDC, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pixelDesc);

	this->renderContext = wglCreateContext(this->hDC);
	b = wglMakeCurrent(this->hDC, this->renderContext);
	glViewport(0, 0, 400, 400);
#elif defined(VTX_PLATFORM_LINUX)
	Bool result = glXMakeCurrent(outputWindow->display, outputWindow->win, outputWindow->context);
	//Bool b = glXMakeContextCurrent(outputWindow->display, outputWindow->win, outputWindow->win, outputWindow->context);
	if(!result)
	{
		XErrorEvent *event = core::NativeWindow::getLastXError(outputWindow->win);
		if(event == NULL)
		{
			std::string message("glXMakeContextCurrent failed with no XErrorEvent");
			VortexBase::engine.output->reportEvent(core::EventOutput::E_LEVEL_FATAL, message);
		}
		else
		{
			std::string message("glXMakeContextCurrent");
			VortexBase::engine.output->reportMethodFailedEvent(core::EventOutput::E_LEVEL_FATAL, message, event->error_code);
		}
		
	}
#endif
}

graphics::OpenGLRender::~OpenGLRender(void)
{
#if defined(VTX_PLATFORM_WIN32)
	wglDeleteContext(this->renderContext);
	ReleaseDC(this->window->getHandle(), this->hDC);
#endif
}

void graphics::OpenGLRender::swap(void)
{
#if defined(VTX_PLATFORM_WIN32)
	glFlush();
	BOOL b = SwapBuffers(this->hDC);
#elif defined(VTX_PLATFORM_LINUX)
	glXSwapBuffers(this->window->display, this->window->win);
#endif
}

void graphics::OpenGLRender::clear(void)
{
	// TODO: Do we need Begin/End methods?
	// This method call shouldnt really be here.
//#if defined(VTX_PLATFORM_WIN32)
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(this->clearColor.values[0], this->clearColor.values[1], this->clearColor.values[2], this->clearColor.values[3]);
//#endif
		
}

graphics::VertexBuffer *graphics::OpenGLRender::createVertexBuffer(graphics::VertexPosNormTex *vertices, core::U32_t noVertices, E_BUFFER_USAGE usage)
{
	return NULL;
}

graphics::Effect *graphics::OpenGLRender::createEffect(core::Allocator &allocator, core::Blob &blob)
{
	return NULL;
}

void graphics::OpenGLRender::bindVertexBuffers(core::U32_t slot, core::U32_t bufferCount, VertexBuffer **buffers, const core::U32_t *strides, const core::U32_t *offsets)
{

}

void graphics::OpenGLRender::draw(core::U32_t verticeCount, core::U32_t startVertex)
{
}

void graphics::OpenGLRender::setPrimitiveType(E_PRIMITIVE_TYPE type)
{
}
