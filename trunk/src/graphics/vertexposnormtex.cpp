//Copyright (C) 2011 Emil Nordén
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either version 2
//of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

#include <graphics/vtx_vertexposnormtex.h>
#include <core/vtx_atomic.h>
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