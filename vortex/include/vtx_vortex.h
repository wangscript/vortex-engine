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

#include "vtx_job.h"
#include "vtx_render.h"
#include "vtx_resource.h"
#include "vtx_simulation.h"

class Root
{
public:
	Root(void);
	void Run(void);
private:
	JobManager			*jobManager;
	SimulationManager	*simulationManager;
	ResourceManager		*resourceManager;
	RenderManager		*renderManager;
};

#endif