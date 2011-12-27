#include <core/vtx_buildconfig.h>

#if defined(VTX_PLATFORM_WIN32)

#include <Windows.h>

#include <core/vtx_cvarsystem.h>
#include <concurrency/vtx_jobmanager.h>
#include <content/vtx_resourcesystem.h>
#include <graphics/vtx_rendermanager.h>
#include <core/vtx_simulationmanager.h>

#include <core/vtx_windowcreationparams.h>
#include <graphics/vtx_rendercreationparams.h>
#include <graphics/vtx_renderapi.h>

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	core::StandardAllocator allocator;
	
	core::WindowCreationParams windParams;
	graphics::RenderCreationParams rendParams;
	rendParams.backBufferSize = windParams.windowSize;

	windParams.isFullscreen = false;
	windParams.windowTitle = "Vortex Game Engine";
	rendParams.rapi = graphics::E_RAPI_DX10;
	
	core::InitCVarSystem(allocator);
	concurrency::InitJobMgr(allocator);
	content::InitResourceSys(allocator);
	graphics::InitRenderMgr(allocator, rendParams, windParams);
	core::InitSimulationMgr(allocator);

	graphics::RenderAPI *render = graphics::renderMgr->getRenderObject();
	core::Vector4 clearColor(1.0f, 1.0f, 0.0f, 1.0f);
	render->setClearColor(clearColor);
	
	core::Clock gameClock, frameClock;
	gameClock.reset();
	frameClock.reset();
	core::F32_t elapsed;
	bool run = true;
	MSG msg;
	while(run)
	{
		// Process all windows messages first
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			switch(msg.message)
			{
			case WM_QUIT:
				run = false;
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			
		}
		
		elapsed = frameClock.getElapsedSeconds();
		if(elapsed > (1.0f / 60.0f))
		{
			//this->runOneFrame(frameClock.getElapsedSecondsAndReset());
			render->clear();
			render->swap();
			frameClock.reset();
		}
	}

	//core::simulationMgr->run();
	
	//ResourceSystem = new graphics::RenderManager(
	/*	this->cvarSystem = new core::CVarSystem(*(new core::StandardAllocator));
	this->output = new core::EventOutput(core::EventOutput::E_LEVEL_VERBOSE);
	this->jobManager = new concurrency::JobManager();
	this->ResourceSystem = new content::ResourceSystem(*this);
	this->renderManager = new graphics::RenderManager(*this);
	this->simulationManager = new core::SimulationManager();*/



	//core::Root root;
	//core::WindowCreationParams winParams;
	//graphics::RenderCreationParams renderParams;

	//winParams.isFullscreen = false;
	//winParams.windowTitle = "Vortex Game Engine";
	//renderParams.backBufferSize = winParams.windowSize;
	//renderParams.rapi = graphics::E_RAPI_DX10;
	//root.Run(winParams, renderParams);
	return 0;
}

#endif