#include "vtx_render.h"
#include "gtest/gtest.h"

TEST(RenderManager, CreateWindow)
{
	RenderManager manager;
	RenderCreationParams renderParams;
	WindowCreationParams windowParams;

	renderParams.rapi = E_RAPI_DX10;
	manager.init(renderParams, windowParams);
	ASSERT_NE(manager.getWindowHandle(), (platform::WINDOW)0);
}