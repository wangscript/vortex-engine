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

#include <platform/vtx_defineconfig.h>
#include <core/vtx_eventoutput.h>
#include <vortex/vtx_job.h>
#include <vortex/vtx_render.h>
#include <vortex/vtx_resource.h>
#include <vortex/vtx_simulation.h>
#include <vortex/vtx_window.h>

class Root
{
public:
	Root(void);
	void Run(WindowCreationParams &windowParams, RenderCreationParams &renderParams);
#if defined(VTX_TOOL_BUILD)
	void toolInit(WindowCreationParams &windowParams, RenderCreationParams &renderParams);
	void toolStep(/*platform::F32*/float elapsed);
	void toolDestroy(void);
#endif
private:
	friend class JobManager;
	friend class SimulationManager;
	friend class ResourceManager;
	friend class RenderManager;
	friend class NativeWindow;
	friend class OpenGLRender;

	EventOutput		*output;
	JobManager		*jobManager;
	SimulationManager	*simulationManager;
	ResourceManager		*resourceManager;
	RenderManager		*renderManager;
};

#endif
