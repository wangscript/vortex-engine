#include <vortex/vtx_vertexposnormtex.h>
#include <platform/vtx_atomic.h>
#include <core/vtx_vector2.h>

graphics::VertexPosNormTex::VertexPosNormTex(
	core::F32_t posX, core::F32_t posY, core::F32_t posZ,
	core::F32_t normX, core::F32_t normY, core::F32_t normZ,
	core::F32_t texU, core::F32_t texV)
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

graphics::VertexPosNormTex::VertexPosNormTex(core::Vector3 &pos, core::Vector3 &norm, core::Vector2<core::F32_t> tex)
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