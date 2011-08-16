#ifndef VTX_D3D10VERTEXBUFFER_H
#define VTX_D3D10VERTEXBUFFER_H

#include <platform/vtx_buildconfig.h>
#include <vortex/vtx_vbuffer.h>

#if defined(VTX_PLATFORM_WIN32) && defined(VTX_COMPILE_WITH_DX10)

namespace graphics
{

	class DX10VertexBuffer : public VertexBuffer
	{
	public:
		ID3D10Buffer *buffer;
		DX10VertexBuffer(ID3D10Buffer *d3dbuffer)
			: buffer(d3dbuffer)
		{
		}
	};

}

#endif

#endif