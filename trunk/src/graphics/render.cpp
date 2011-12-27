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

#include <core/vtx_buildconfig.h>
#include <graphics/vtx_rendermanager.h>
#if defined(VTX_COMPILE_WITH_DX10)
#include <graphics/vtx_dx10render.h>
#endif
#if defined(VTX_COMPILE_WITH_OPENGL)
#include <graphics/vtx_openglrender.h>
#endif

#include <core/vtx_assertions.h>
#include <core/vtx_vortex.h>
#include <core/vtx_nativewindow.h>
#include <core/vtx_eventoutput.h>
#include <graphics/vtx_rendercreationparams.h>

#include <core/vtx_standardallocator.h>

namespace core
{
	class WindowCreationParams;
}

graphics::RenderManager *graphics::renderMgr;

void graphics::InitRenderMgr(core::Allocator &allocator, graphics::RenderCreationParams &params, core::WindowCreationParams &windowParams)
{
	core::StandardAllocator *renderMgrAlloc = new (allocator.allocate(sizeof(core::StandardAllocator))) core::StandardAllocator;
	graphics::renderMgr = new (allocator.allocate(sizeof(graphics::RenderManager))) graphics::RenderManager(*renderMgrAlloc, params, windowParams);
}

graphics::RenderManager::RenderManager(core::Allocator &allocator, graphics::RenderCreationParams &params, core::WindowCreationParams &windowParams)
	: alloc(allocator)
{
	this->render = NULL;
	
	this->window = core::NativeWindow::create(windowParams);
	//this->createWindow(windowParams);
#if defined(VTX_COMPILE_WITH_DX10)
	if(params.rapi == E_RAPI_DX10)
	{
		//core::VortexBase::engine.output->reportEvent(core::EventOutput::E_LEVEL_VERBOSE, "RenderManager: Creating DX10 render");
		this->render = new DX10Render(params, this->window);
	}
#endif
#if defined(VTX_COMPILE_WITH_OPENGL)
	if(this->render == NULL && params.rapi == E_RAPI_OPENGL)
	{
		//core::VortexBase::engine.output->reportEvent(core::EventOutput::E_LEVEL_VERBOSE, "RenderManager: Creating OpenGL render");	
		this->render = new OpenGLRender(params, this->window);
	}
#endif

	ASSERT(this->render != NULL);
}

graphics::RenderManager::~RenderManager()
{
	this->window->destroy();
}

graphics::RenderAPI *graphics::RenderManager::getRenderObject(void)
{
	return this->render;
}

void graphics::RenderManager::createWindow(core::WindowCreationParams &params)
{

}