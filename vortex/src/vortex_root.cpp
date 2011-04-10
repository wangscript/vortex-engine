#include "vtx_vortex.h"

Root::Root()
{
	this->jobManager = new JobManager();
	this->resourceManager = new ResourceManager();
	this->renderManager = new RenderManager();
	this->simulationManager = new SimulationManager();
}

void Root::Run()
{
	this->jobManager->init();
	this->resourceManager->init();
	this->renderManager->init();
	this->simulationManager->init();

	this->simulationManager->run();

	this->jobManager->destroy();
	this->simulationManager->destroy();
	this->renderManager->destroy();
	this->resourceManager->destroy();

}