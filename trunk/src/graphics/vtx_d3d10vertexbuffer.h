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

#ifndef VTX_D3D10VERTEXBUFFER_H
#define VTX_D3D10VERTEXBUFFER_H

#include <core/vtx_buildconfig.h>
#include <graphics/vtx_vbuffer.h>

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