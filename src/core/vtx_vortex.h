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

#ifndef VTX_VORTEX_H
#define VTX_VORTEX_H

#include <core/vtx_buildconfig.h>
#include <core/vtx_atomic.h>

namespace graphics
{
	class RenderCreationParams;
	class RenderManager;
	class OpenGLRender;
}

namespace concurrency
{
	class JobManager;
}

namespace content
{
	class ResourceManager;
}

namespace core
{
	class EventOutput;
	class NativeWindow;
	class SimulationManager;
	class WindowCreationParams;

	class Root
	{
	public:
		Root(void);
		void Run(core::WindowCreationParams &windowParams, graphics::RenderCreationParams &renderParams);
#if defined(VTX_TOOL_BUILD)
		void toolInit(core::WindowCreationParams &windowParams, graphics::RenderCreationParams &renderParams);
		void toolStep(core::F32_t elapsed);
		void toolDestroy(void);
#endif
	private:
		friend class JobManager;
		friend class SimulationManager;
		friend class ResourceManager;
		friend class graphics::RenderManager;
		friend class NativeWindow;
		friend class graphics::OpenGLRender;

		core::EventOutput		*output;
		concurrency::JobManager		*jobManager;
		core::SimulationManager		*simulationManager;
		content::ResourceManager	*resourceManager;
		graphics::RenderManager		*renderManager;

		void init(core::WindowCreationParams &windowParams, graphics::RenderCreationParams &renderParams);
	};

}

#endif
