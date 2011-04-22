#ifndef VTX_DEFINECONFIG_H
#define VTX_DEFINECONFIG_H

#if defined(WIN32)
#define VTX_PLATFORM_WIN32
#endif

/*	Render API defines
	Comment out a define to not include it in the build. */
#if defined(VTX_PLATFORM_WIN32)
#define VTX_COMPILE_WITH_DX10
//#define VTX_COMPILE_WITH_DX11
//#define VTX_COMPILE_WITH_OPENGL
#endif


#if defined(VTX_COMPILE_WITH_DX10)
#pragma comment(lib, "DXGI.lib")
#pragma comment(lib, "D3D10.lib")
#endif

#endif