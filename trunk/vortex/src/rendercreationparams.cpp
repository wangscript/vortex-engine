#include "vtx_render.h"

#define DEFAULT_BACKBUFFER_WIDTH	800
#define DEFAULT_BACKBUFFER_HEIGHT	600

RenderCreationParams::RenderCreationParams(void)
{
	this->backBufferSize.x = DEFAULT_BACKBUFFER_WIDTH;
	this->backBufferSize.y = DEFAULT_BACKBUFFER_HEIGHT;
	this->multisampleCount = 1;
	this->multisampleQuality = 0;
	this->rapi = E_RAPI_SOFTWARE; // Software rendering by default.
}