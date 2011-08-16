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

#include <core/vtx_eventoutput.h>
#include <vortex/vtx_resource.h>
#include <vortex/vtx_rendermanager.h>
#include <vortex/vtx_simulationmanager.h>

#define INIT(init_exp, component) \
	{ \
		std::wstring message(L"Initializing "); \
		message.append(component); \
		message.append(L"..."); \
		this->output->reportEvent(EventOutput::E_LEVEL_VERBOSE, message); \
		init_exp \
		message.insert(0, L"Done "); \
		message.erase(message.length() - 3, 3); \
		this->output->reportEvent(EventOutput::E_LEVEL_VERBOSE, message); \
	}
	
#include <vortex/vtx_jobmanager.h>
#include <vortex/vtx_vortex.h>
#include <iostream>

core::Root::Root()
{
	std::wstring msg(L"Standard error output!!");
	this->output = new core::EventOutput(core::EventOutput::E_LEVEL_VERBOSE);
	this->output->reportEvent(core::EventOutput::E_LEVEL_FATAL, msg);
	this->jobManager = new concurrency::JobManager();
	this->resourceManager = new content::ResourceManager(*this);
	this->renderManager = new graphics::RenderManager(*this);
	this->simulationManager = new core::SimulationManager();
}

void core::Root::Run(core::WindowCreationParams &windowParams, graphics::RenderCreationParams &renderParams)
{	
	this->init(windowParams, renderParams);

	this->simulationManager->run();

	this->jobManager->destroy();
	this->simulationManager->destroy();
	this->renderManager->destroy();
	this->resourceManager->destroy();

}

void core::Root::init(core::WindowCreationParams &windowParams, graphics::RenderCreationParams &renderParams)
{
	INIT(this->jobManager->init();, L"JobManager");
	INIT(this->resourceManager->init();, L"ResourceManager");
	INIT(this->renderManager->init(renderParams, windowParams);, L"RenderManager");
	INIT(this->simulationManager->init(this->renderManager->getRenderObject());, L"SimulationManager");
}

#if defined(VTX_TOOL_BUILD)
void core::Root::toolInit(WindowCreationParams &windowParams, RenderCreationParams &renderParams)
{
	this->init(windowParams, renderParams);
}

void core::Root::toolStep(/*platform::F32*/float elapsed)
{
	this->simulationManager->step(elapsed);
}

void core::Root::toolDestroy(void)
{
	this->jobManager->destroy();
	this->simulationManager->destroy();
	this->renderManager->destroy();
	this->resourceManager->destroy();
}
#endif
