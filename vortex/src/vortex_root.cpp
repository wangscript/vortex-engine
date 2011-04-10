#include "vtx_vortex.h"

Root::Root()
{
	this->resourceManager = new ResourceManager();
	this->renderManager = new RenderManager();
	this->simulationManager = new SimulationManager();
}

void Root::Run()
{
	this->resourceManager->init();
	this->renderManager->init();
	this->simulationManager->init();

	this->simulationManager->run();

	this->simulationManager->destroy();
	this->renderManager->destroy();
	this->resourceManager->destroy();

}