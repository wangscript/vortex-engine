#ifndef VTX_VERTEXPOSNORMTEX_H
#define VTX_VERTEXPOSNORMTEX_H

#include <platform/vtx_atomic.h>
#include <core/vtx_vector2.h>
#include <core/vtx_vector3.h>

namespace graphics
{

	struct VertexPosNormTex
	{
	public:
		core::Vector3 position;
		core::Vector3 normal;
		core::Vector2<core::F32_t> texCoord;

		VertexPosNormTex()
		{
		}

		VertexPosNormTex(core::Vector3 &pos, core::Vector3 &norm, core::Vector2<core::F32_t> tex);

		// C++ does not support constructor chaining?
		VertexPosNormTex(
			core::F32_t posX, core::F32_t posY, core::F32_t posZ,
			core::F32_t normX, core::F32_t normY, core::F32_t normZ,
			core::F32_t texU, core::F32_t texV);
		//D3DXVECTOR3 position;
		//D3DXVECTOR3 normal;
		//D3DXVECTOR2 uv;
	};

}

#endif