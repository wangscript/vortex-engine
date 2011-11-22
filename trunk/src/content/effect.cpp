#include <core/vtx_buildconfig.h>
#include <graphics/vtx_effect.h>
#include <core/vtx_blob.h>
#include <graphics/vtx_renderapi.h>

#if defined(VTX_PLATFORM_WIN32) && defined (VTX_COMPILE_WITH_DX10)
#include <D3D10effect.h>
#endif