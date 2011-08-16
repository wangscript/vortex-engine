#ifndef VTX_VBUFFER_H
#define VTX_VBUFFER_H

#include <platform/vtx_atomic.h>

namespace graphics
{

	enum E_BUFFER_USAGE
	{
		E_BUFFER_USAGE_IMMUTABLE,
		E_BUFFER_USAGE_DYNAMIC,
	};

	class VertexBuffer
	{
	protected:
		VertexBuffer(void)
		{
		}
	};

}


#endif