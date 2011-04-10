#ifndef VTX_VORTEX_H
#define VTX_VORTEX_H

#include "vtx_render.h"
#include "vtx_resource.h"
#include "vtx_simulation.h"

class Root
{
public:
	Root(void);
	void Run(void);
private:
	SimulationManager	*simulationManager;
	ResourceManager		*resourceManager;
	RenderManager		*renderManager;
};

#endif