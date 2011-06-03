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

#include <platform/vtx_defineconfig.h>
#include <vortex/vtx_render.h>
#if defined(VTX_COMPILE_WITH_DX10)
#include <vortex/vtx_dx10render.h>
#endif
#if defined(VTX_COMPILE_WITH_OPENGL)
#include <vortex/vtx_openglrender.h>
#endif

#include <core/vtx_assertions.h>
//#if defined(VTX_PLATFORM_WIN32)
//#include <Windows.h>
//#endif

using namespace platform;

RenderManager::RenderManager(Root& parent) : VortexBase(parent)
{
	this->render = NULL;
}

void RenderManager::init(RenderCreationParams &params, WindowCreationParams &windowParams)
{
	this->window = NativeWindow::create(VortexBase::engineParent, windowParams);
	//this->createWindow(windowParams);
#if defined(VTX_COMPILE_WITH_DX10)
	if(params.rapi == E_RAPI_DX10)
	{
		this->render = new DX10Render(VortexBase::engineParent, params, this->window);
	}
#endif
#if defined(VTX_COMPILE_WITH_OPENGL)
	if(this->render == NULL && params.rapi == E_RAPI_OPENGL)
	{
		this->render = new OpenGLRender(VortexBase::engineParent, params, this->window);
	}
#endif
}

void RenderManager::destroy(void)
{
	this->window->destroy();
}

RenderAPI *RenderManager::getRenderObject(void)
{
	return this->render;
}

void RenderManager::createWindow(WindowCreationParams &params)
{

}
