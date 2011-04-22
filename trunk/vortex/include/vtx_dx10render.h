#ifndef VTX_RENDERDX10_H
#define VTX_RENDERDX10_H

#include "vtx_renderinternal.h"
#include "vtx_render.h"
#include "vtx_atomic.h"
#include <d3d10.h>

class DX10Render : public RenderAPI
{
private:
	ID3D10Device *device;
	IDXGISwapChain *swapChain;
	ID3D10RenderTargetView *renderTargetView;
public:
	DX10Render(RenderCreationParams &params, platform::WINDOW outputWindow);
	virtual void swap(void);
	virtual void clear(void);
};

#endif