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

#ifndef VTX_RENDERDRIVER_H
#define VTX_RENDERDRIVER_H

#include <core/vtx_types.h>
#include <vortex/vtx_vortexbase.h>
#include <vortex/vtx_vbuffer.h>
#include <platform/vtx_atomic.h>

enum E_PRIMITIVE_TYPE
{
	E_PRIMITIVE_POINTLIST,
	E_PRIMITIVE_LINELIST,
	E_PRIMITIVE_LINESTRIP,
	E_PRIMITIVE_TRIANGLELIST,
	E_PRIMITIVE_TRIANGLESTRIP,
	E_PRIMITIVE_LINELIST_ADJ,
	E_PRIMITIVE_LINESTRIP_ADJ,
	E_PRIMITIVE_TRIANGLELIST_ADJ,
	E_PRIMITIVE_TRIANGLESTRIP_ADJ
};

// Forward declare
struct VertexPosNormTex;

class RenderAPI : protected VortexBase
{
protected:
	core::Vector4 clearColor;
	RenderAPI(Root& parent) : VortexBase(parent) {} //Empty constructor
public:
	static RenderAPI *createDX10(void);
	virtual void swap(void) = 0;
	virtual void clear() = 0;
	void setClearColor(core::Vector4 &color);
	core::Vector4 *getClearColor();

	virtual VertexBuffer *createVertexBuffer(VertexPosNormTex *vertices, platform::U32_t noVertices, E_BUFFER_USAGE usage) = 0;
	virtual void bindVertexBuffers(platform::U32_t slot, platform::U32_t bufferCount, VertexBuffer **buffers, const platform::U32_t *strides, const platform::U32_t *offsets) = 0;
	virtual void draw(platform::U32_t verticeCount, platform::U32_t startVertex) = 0;
	virtual void setPrimitiveType(E_PRIMITIVE_TYPE type) = 0;
};

#endif
