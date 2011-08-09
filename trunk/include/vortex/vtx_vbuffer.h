#ifndef VTX_VBUFFER_H

#include <core/vtx_types.h>

struct VertexPosNormTex
{
	core::Vector3 position;
	core::Vector3 normal;
	core::Vector2<platform::F32> texCoord;
	//D3DXVECTOR3 position;
	//D3DXVECTOR3 normal;
	//D3DXVECTOR2 uv;
};

enum E_BUFFER_USAGE
{
	BUFFER_USAGE_IMMUTABLE,
	BUFFER_USAGE_DYNAMIC,
};

class VertexBuffer
{
protected:
	VertexBuffer(void)
	{
	}
};


#endif