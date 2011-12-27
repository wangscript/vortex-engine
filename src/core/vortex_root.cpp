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


#include <core/vtx_eventoutput.h>
#include <content/vtx_ResourceSystem.h>
#include <graphics/vtx_rendermanager.h>
#include <core/vtx_simulationmanager.h>

#define INIT(init_exp, component) \
	{ \
		std::string message("Initializing "); \
		message.append(component); \
		message.append("..."); \
		this->output->reportEvent(EventOutput::E_LEVEL_VERBOSE, message); \
		init_exp \
		message.insert(0, "Done "); \
		message.erase(message.length() - 3, 3); \
		this->output->reportEvent(EventOutput::E_LEVEL_VERBOSE, message); \
	}
	
#include <concurrency/vtx_jobmanager.h>
#include <core/vtx_vortex.h>
#include <iostream>

core::Root::Root()
{
	////this->cvarSystem = new core::CVarSystem(*(new core::StandardAllocator));
	//this->output = new core::EventOutput(core::EventOutput::E_LEVEL_VERBOSE);
	//this->jobManager = new concurrency::JobManager();
	//this->ResourceSystem = new content::ResourceSystem(*this);
	//this->renderManager = new graphics::RenderManager(*this);
	//this->simulationManager = new core::SimulationManager();
}

void core::Root::Run(core::WindowCreationParams &windowParams, graphics::RenderCreationParams &renderParams)
{	
	//this->init(windowParams, renderParams);

	//this->simulationManager->run();

	//this->jobManager->destroy();
	//this->simulationManager->destroy();
	//this->renderManager->destroy();
	//this->ResourceSystem->destroy();

}

void core::Root::readConfig(std::string& path)
{
}


void core::Root::init(core::WindowCreationParams &windowParams, graphics::RenderCreationParams &renderParams)
{
	//INIT(this->jobManager->init();, "JobManager");
	//INIT(this->ResourceSystem->init();, "ResourceSystem");
	//INIT(this->renderManager->init(renderParams, windowParams);, "RenderManager");
	//INIT(this->simulationManager->init(this->renderManager->getRenderObject());, "SimulationManager");
}

#if defined(VTX_TOOL_BUILD)
void core::Root::toolInit(core::WindowCreationParams &windowParams, graphics::RenderCreationParams &renderParams)
{
	this->init(windowParams, renderParams);
}

void core::Root::toolStep(core::F32_t elapsed)
{
	this->simulationManager->step(elapsed);
}

void core::Root::toolDestroy(void)
{
	this->jobManager->destroy();
	this->simulationManager->destroy();
	this->renderManager->destroy();
	this->ResourceSystem->destroy();
}
#endif
