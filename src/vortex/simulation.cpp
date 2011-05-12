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
#include <vortex/vtx_simulation.h>
#include <vortex/vtx_clock.h>
#include <stdlib.h>
#include <ctime>
#include <iostream>

#if defined(VTX_PLATFORM_WIN32)
#include <Windows.h>
#endif

using namespace platform;

void SimulationManager::init(RenderAPI *render)
{
	this->render = render;
	srand(time(NULL));
}

void SimulationManager::destroy()
{
}

void SimulationManager::run()
{
	core::Vector4 color(1.0f, 0.0f, 0.0f, 1.0f);
	Clock gameClock, frameClock;
	gameClock.reset();
	frameClock.reset();
	while(true)
	{
		color.values[0] = (platform::F32)((rand() % 101) / 100.0f);
		color.values[1] = (platform::F32)((rand() % 101) / 100.0f);
		color.values[2] = (platform::F32)((rand() % 101) / 100.0f);
		this->render->setClearColor(color);
		// Message pump. Win32 only.
#if defined(VTX_PLATFORM_WIN32)
		MSG msg;
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
#endif
		this->runOneFrame(frameClock.getElapsedSecondsAndReset());
		frameClock.reset();
	};
}

void SimulationManager::runOneFrame(F32 seconds)
{
	this->frames++;
	//std::cout << seconds << std::endl;
	//std::cout << "pre clear " << this->frames << std::endl;
	this->render->clear();
	//std::cout << "post clear " << this->frames << std::endl;
	// DRAW

	this->render->swap();
}
