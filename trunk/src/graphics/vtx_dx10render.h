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

#ifndef VTX_RENDERDX10_H
#define VTX_RENDERDX10_H

#include <core/vtx_buildconfig.h>

#if defined(VTX_PLATFORM_WIN32) && defined(VTX_COMPILE_WITH_DX10)

#include <graphics/vtx_renderapi.h>
#include <core/vtx_atomic.h>
#include <d3d10.h>
#include <D3DX10.h>

#ifndef ReleaseCOM
#define ReleaseCOM(x) if (x) { x->Release(); x = NULL; }
#endif

namespace core
{
	class NativeWindow;
}
//D3D10_INPUT_ELEMENT_DESC VertexPositionNormalTextureDesc[] =
//{
//	{"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0},
//	{"NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0},
//	{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0}
//};

//class DX10VertexBuffer : VertexBuffer
//{
//private:
//	ID3D10Buffer *buffer;
//	public 
//};

namespace graphics
{
	class RenderCreationParams;

	class DX10Render : public RenderAPI
	{
	private:
		ID3D10Device *device;
		IDXGISwapChain *swapChain;
		ID3D10RenderTargetView *renderTargetView;
	public:
		DX10Render(core::Root &parent, graphics::RenderCreationParams &params, core::NativeWindow *outputWindow);
		virtual void swap(void);
		virtual void clear(void);
		virtual VertexBuffer *createVertexBuffer(VertexPosNormTex *vertices, core::U32_t noVertices, E_BUFFER_USAGE usage);
		virtual void bindVertexBuffers(core::U32_t slot, core::U32_t bufferCount, VertexBuffer **buffers, const core::U32_t *strides, const core::U32_t *offsets);
		virtual void draw(core::U32_t verticeCount, core::U32_t startVertex);
		virtual void setPrimitiveType(E_PRIMITIVE_TYPE type);
	};

}

#endif

#endif
