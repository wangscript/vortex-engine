#include <graphics/vtx_dx10effect.h>
#include <core/vtx_blob.h>
#include <core/vtx_vortex.h>
#include <graphics/vtx_rendermanager.h>
#include <graphics/vtx_renderapi.h>

void graphics::DX10Effect::init(core::Root &root, core::Blob &blob)
{
	graphics::RenderAPI *renderAPI = root.renderManager->getRenderObject();
	//renderAPI->createEffect(
}