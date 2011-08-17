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
#include <core/vtx_simulationmanager.h>
#include <core/vtx_clock.h>
#include <graphics/vtx_renderapi.h>
#include <iostream>
#include <ctime>
#include <stdlib.h>
#if defined(VTX_PLATFORM_WIN32)
#include <Windows.h>
#endif

#include <graphics/vtx_vertexposnormtex.h>
#include <graphics/vtx_vbuffer.h>

void core::SimulationManager::init(graphics::RenderAPI *render)
{
	this->render = render;
}

void core::SimulationManager::destroy()
{
}

void core::SimulationManager::run()
{
	core::Clock gameClock, frameClock;
	core::Vector4 color(0.0f, 0.0f, 0.5f, 1.0f);
	this->render->setClearColor(color);
	gameClock.reset();
	frameClock.reset();
	core::F32_t elapsed;
	
	while(true)
	{
		
		// Message pump. Win32 only.
#if defined(VTX_PLATFORM_WIN32)
		MSG msg;
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
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
	
	graphics::VertexPosNormTex verts[] =
	{
		graphics::VertexPosNormTex(-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f),
		graphics::VertexPosNormTex(0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 0.0f),
		graphics::VertexPosNormTex(1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f)
	};

	U32_t stride = sizeof(graphics::VertexPosNormTex);
	U32_t offset = 0;
	graphics::VertexBuffer *vb = this->render->createVertexBuffer(verts, 3, graphics::E_BUFFER_USAGE_IMMUTABLE);
	this->render->bindVertexBuffers(0, 1, &vb, &stride, &offset);
	this->render->setPrimitiveType(graphics::E_PRIMITIVE_TRIANGLESTRIP);
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
	this->render->draw(3, 0);
	this->render->swap();
}