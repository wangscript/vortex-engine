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

#ifndef VTX_OPENGLRENDER_H
#define VTX_OPENGLRENDER_H

#include <vortex/vtx_renderinternal.h>
#include <vortex/vtx_render.h>

class OpenGLRender : public RenderAPI
{
private:
	NativeWindow *window;
#if defined(VTX_PLATFORM_WIN32)
	HDC hDC;
	HGLRC renderContext;
#endif
public:
	OpenGLRender(Root& parent, RenderCreationParams &params, NativeWindow *outputWindow);
	~OpenGLRender(void);
	virtual void swap(void);
	virtual void clear(void);
};

#endif
