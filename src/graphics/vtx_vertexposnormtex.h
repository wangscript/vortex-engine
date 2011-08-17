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

#ifndef VTX_VERTEXPOSNORMTEX_H
#define VTX_VERTEXPOSNORMTEX_H

#include <core/vtx_atomic.h>
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