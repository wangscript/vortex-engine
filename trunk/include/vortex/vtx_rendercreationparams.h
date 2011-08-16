#ifndef VTX_RENDERCREATIONPARAMS_H
#define VTX_RENDERCREATIONPARAMS_H

#include <platform/vtx_atomic.h>
#include <core/vtx_vector2.h>

namespace graphics
{

	enum E_RENDER_API
	{
		// TODO: Should all enum members be included despite an undefined directive?
		// The check could be performed in init()
		// It would provide a more stable interface, less confusion on the developer.
#ifdef VTX_COMPILE_WITH_DX10
		E_RAPI_DX10,
#endif
#ifdef VTX_COMPILE_WITH_DX11
		E_RAPI_DX11,
#endif
#ifdef VTX_COMPILE_WITH_OPENGL
		E_RAPI_OPENGL,
#endif
		E_RAPI_SOFTWARE
	};

	class RenderCreationParams
	{
	public:
		RenderCreationParams(void);
		E_RENDER_API rapi;
		core::Vector2<core::U32_t> backBufferSize;
		core::U32_t multisampleCount;
		core::U32_t multisampleQuality;
	};

}

#endif