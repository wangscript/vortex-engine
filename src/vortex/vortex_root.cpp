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

#define INIT(init_exp, component) \
	{ \
		std::wstring message(L"Initializing "); \
		message.append(component); \
		message.append(L"...\n"); \
		this->output->reportEvent(EventOutput::E_LEVEL_VERBOSE, message); \
		init_exp \
		message.insert(0, L"Done "); \
		message.erase(message.length() - 4, 3); \
		this->output->reportEvent(EventOutput::E_LEVEL_VERBOSE, message); \
	}
	

#include <vortex/vtx_vortex.h>
#include <iostream>

Root::Root()
{
	std::wstring msg(L"Standard error output!!");
	this->output = new EventOutput(EventOutput::E_LEVEL_VERBOSE);
	this->output->reportEvent(EventOutput::E_LEVEL_FATAL, msg);
	this->jobManager = new JobManager;
	this->resourceManager = new ResourceManager(*this);
	this->renderManager = new RenderManager(*this);
	this->simulationManager = new SimulationManager;
}

void Root::Run(WindowCreationParams &windowParams, RenderCreationParams &renderParams)
{	
	this->init(windowParams, renderParams);

	this->simulationManager->run();

	this->jobManager->destroy();
	this->simulationManager->destroy();
	this->renderManager->destroy();
	this->resourceManager->destroy();

}

void Root::init(WindowCreationParams &windowParams, RenderCreationParams &renderParams)
{
	INIT(this->jobManager->init();, L"JobManager");
	INIT(this->resourceManager->init();, L"ResourceManager");
	INIT(this->renderManager->init(renderParams, windowParams);, L"RenderManager");
	INIT(this->simulationManager->init(this->renderManager->getRenderObject());, L"SimulationManager");
}

#if defined(VTX_TOOL_BUILD)
void Root::toolInit(WindowCreationParams &windowParams, RenderCreationParams &renderParams)
{
	this->init(windowParams, renderParams);
}

void Root::toolStep(/*platform::F32*/float elapsed)
{
	this->simulationManager->step(elapsed);
}

void Root::toolDestroy(void)
{
	this->jobManager->destroy();
	this->simulationManager->destroy();
	this->renderManager->destroy();
	this->resourceManager->destroy();
}
#endif
