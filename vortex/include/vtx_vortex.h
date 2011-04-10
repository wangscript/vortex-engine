#ifndef VTX_VORTEX_H
#define VTX_VORTEX_H

#include "vtx_job.h"
#include "vtx_render.h"
#include "vtx_resource.h"
#include "vtx_simulation.h"

class Root
{
public:
	Root(void);
	void Run(void);
private:
	JobManager			*jobManager;
	SimulationManager	*simulationManager;
	ResourceManager		*resourceManager;
	RenderManager		*renderManager;
};

#endif