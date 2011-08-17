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

#include <core/vtx_atomic.h>
#include <core/vtx_clock.h>

namespace graphics
{
	class RenderAPI;
}

namespace core
{

	class SimulationManager
	{
	public:
		core::U32_t frames;
		void init(graphics::RenderAPI *render);
		void destroy(void);
		void run(void);
		void step(core::F32_t elapsed);
	private:
		core::Clock gameClock;
		graphics::RenderAPI *render;
		void runOneFrame(core::F32_t seconds);
	};

}

#endif
