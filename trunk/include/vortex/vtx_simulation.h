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

#ifndef VTX_SIMULATION_H
#define VTX_SIMULATION_H
//#include <vortex/vtx_vortexbase.h>
#include <vortex/vtx_renderinternal.h>
#include <platform/vtx_atomic.h>
#include <vortex/vtx_clock.h>

class SimulationManager
{
public:
	platform::U32 frames;
	void init(RenderAPI *render);
	void destroy(void);
	void run(void);
	void step(/*platform::F32*/ float elapsed);
private:
	Clock gameClock;
	RenderAPI *render;
	void runOneFrame(/*platform::F32*/ float seconds);
};

#endif
