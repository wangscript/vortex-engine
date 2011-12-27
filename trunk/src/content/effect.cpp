#include <core/vtx_buildconfig.h>
#include <graphics/vtx_effect.h>
#include <core/vtx_blob.h>
#include <graphics/vtx_renderapi.h>
#include <core/vtx_vortex.h>
#include <graphics/vtx_rendermanager.h>
#include <graphics/vtx_dx10render.h>

#if defined(VTX_PLATFORM_WIN32) && defined (VTX_COMPILE_WITH_DX10)
#include <D3D10effect.h>
#include <d3d10.h>
#include <D3DX10.h>
#endif

void graphics::Effect::init(core::Blob &blob)
{
#if defined(VTX_COMPILE_WITH_DX10)
	ID3D10Effect *effect;
	// TODO: Investigate if theres anyway to supply a custom allocator to D3D.
	//ID3D10Device *device = static_cast<graphics::DX10Render*>(VortexBase::engine.renderManager->getRenderObject())->getDevice();
	//HRESULT result = D3D10CreateEffectFromMemory(const_cast<void*>(blob.getPtr()), static_cast<SIZE_T>(blob.getSize()), 0, device, NULL, &effect);
	//ID3D10Effect *d3dEffect;
	//if(SUCCEEDED(result))
	{

		//effect = new (allocator.allocate(sizeof(graphics::DX10Effect))) graphics::DX10Effect(VortexBase::engine, *d3dEffect);
	}
#endif
}