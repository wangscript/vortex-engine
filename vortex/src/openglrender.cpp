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

#include "vtx_openglrender.h"
#include <gl\GL.h>

OpenGLRender::OpenGLRender(RenderCreationParams &params, platform::WINDOW outputWindow)
{
	this->windowHandle = outputWindow;
#if defined(VTX_PLATFORM_WIN32)
	this->hDC = GetDC(outputWindow);
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

#endif
}

OpenGLRender::~OpenGLRender(void)
{
#if defined(VTX_PLATFORM_WIN32)
	wglDeleteContext(this->renderContext);
	ReleaseDC(this->windowHandle, this->hDC);
#endif
}

void OpenGLRender::swap(void)
{
#if defined(VTX_PLATFORM_WIN32)
	glFlush();
	BOOL b = SwapBuffers(this->hDC);
#endif
}

void OpenGLRender::clear(void)
{
	// TODO: Do we need Begin/End methods?
	// This method call shouldnt really be here.
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(this->clearColor.values[0], this->clearColor.values[1], this->clearColor.values[2], this->clearColor.values[3]);
		
}