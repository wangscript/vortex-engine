//Copyright (C) 2011 Emil Nord�n
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
#include <core/vtx_simulationmanager.h>
#include <core/vtx_clock.h>
#include <graphics/vtx_renderapi.h>
#include <iostream>
#include <ctime>
#include <stdlib.h>
#if defined(VTX_PLATFORM_WIN32)
#include <Windows.h>
#endif


#include <graphics/vtx_rendermanager.h>

#include <core/vtx_standardallocator.h>

core::SimulationManager *core::simulationMgr;

void core::InitSimulationMgr(core::Allocator &allocator)
{
	core::StandardAllocator *simulationMgrAlloc = new (allocator.allocate(sizeof(core::StandardAllocator))) core::StandardAllocator;
	core::simulationMgr = new (allocator.allocate(sizeof(core::SimulationManager))) core::SimulationManager(*simulationMgrAlloc);
}

core::SimulationManager::SimulationManager(core::Allocator &allocator)
	: alloc(allocator)
{

}

void core::SimulationManager::run()
{
	this->render = graphics::renderMgr->getRenderObject();
	core::Clock gameClock, frameClock;
	core::Vector4 color(1.0f, 1.0f, 1.0f, 1.0f);
	this->render->setClearColor(color);
	gameClock.reset();
	frameClock.reset();
	core::F32_t elapsed;

	bool isRunning = true;
	while(isRunning)
	{
		
		// Message pump. Win32 only.
#if defined(VTX_PLATFORM_WIN32)
		MSG msg;

		
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			switch(msg.message)
			{
			case WM_QUIT:
				isRunning = false;
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
#endif
		elapsed = frameClock.getElapsedSeconds();
		if(elapsed > (1.0f / 60.0f))
		{
			//this->runOneFrame(frameClock.getElapsedSecondsAndReset());
			this->runOneFrame(elapsed);
			frameClock.reset();
		}
		
	};
}

void core::SimulationManager::step(core::F32_t elapsed)
{
	std::cout << "TESTING" << std::endl;
	core::Vector4 color(0.25f, elapsed, 1.0f, 1.0f);
	this->render->setClearColor(color);
	this->runOneFrame(elapsed);
}

void core::SimulationManager::runOneFrame(core::F32_t seconds)
{
	this->frames++;
	//std::cout << seconds << std::endl;
	//std::cout << "pre clear " << this->frames << std::endl;
	this->render->clear();
	//std::cout << "post clear " << this->frames << std::endl;
	// DRAW
	//this->render->draw(3, 0);
	this->render->swap();
}
