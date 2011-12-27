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

#ifndef VTX_OPENGLRENDER_H
#define VTX_OPENGLRENDER_H

#include <graphics/vtx_renderapi.h>
#include <graphics/vtx_rendermanager.h>

namespace core
{
	class Allocator;
	class NativeWindow;
}

namespace graphics
{
	class RenderCreationParams;
	class VertexBuffer;
	class VertexPosNormTex;

	class OpenGLRender : public graphics::RenderAPI
	{
	private:
		core::NativeWindow *window;
#if defined(VTX_PLATFORM_WIN32)
		HDC hDC;
		HGLRC renderContext;
#endif
	public:
		OpenGLRender(graphics::RenderCreationParams &params, core::NativeWindow *outputWindow);
		~OpenGLRender(void);
		virtual void swap(void);
		virtual void clear(void);
		virtual VertexBuffer *createVertexBuffer(graphics::VertexPosNormTex *vertices, core::U32_t noVertices, graphics::E_BUFFER_USAGE usage);
		virtual Effect *createEffect(core::Allocator &allocator, core::Blob &blob);
		virtual void bindVertexBuffers(core::U32_t slot, core::U32_t bufferCount, graphics::VertexBuffer **buffers, const core::U32_t *strides, const core::U32_t *offsets);
		virtual void draw(core::U32_t verticeCount, core::U32_t startVertex);
		virtual void setPrimitiveType(graphics::E_PRIMITIVE_TYPE type);
	};

}

#endif
