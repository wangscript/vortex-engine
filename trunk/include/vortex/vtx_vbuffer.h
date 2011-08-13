#ifndef VTX_VBUFFER_H

#include <core/vtx_types.h>
#include <platform/vtx_atomic.h>

struct VertexPosNormTex
{
public:
	core::Vector3 position;
	core::Vector3 normal;
	core::Vector2<platform::F32_t> texCoord;

	VertexPosNormTex()
	{
	}

	VertexPosNormTex(core::Vector3 &pos, core::Vector3 &norm, core::Vector2<platform::F32_t> tex)
	{
		position.x = pos.x;
		position.y = pos.y;
		position.z = pos.z;

		normal.x = norm.x;
		normal.y = norm.y;
		normal.z = norm.z;

		texCoord.x = tex.x;
		texCoord.y = tex.y;
	}

	// C++ does not support constructor chaining?
	VertexPosNormTex(
		platform::F32_t posX, platform::F32_t posY, platform::F32_t posZ,
		platform::F32_t normX, platform::F32_t normY, platform::F32_t normZ,
		platform::F32_t texU, platform::F32_t texV)
	{
		position.x = posX;
		position.y = posY;
		position.z = posZ;

		normal.x = normX;
		normal.y = normY;
		normal.z = normZ;

		texCoord.x = texU;
		texCoord.y = texV;
	}
	//D3DXVECTOR3 position;
	//D3DXVECTOR3 normal;
	//D3DXVECTOR2 uv;
};

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


#endif