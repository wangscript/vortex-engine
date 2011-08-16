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

#define ASSERTIONS_ENABLED 1
#include <platform/vtx_buildconfig.h>
#include <vortex/vtx_dx10render.h>
#include <core/vtx_assertions.h>
#include <vortex/vtx_rendercreationparams.h>
#include <vortex/vtx_d3d10vertexbuffer.h>
#include <vortex/vtx_nativewindow.h>
#include <vortex/vtx_vertexposnormtex.h>

#if defined(VTX_PLATFORM_WIN32) && defined(VTX_COMPILE_WITH_DX10)

graphics::DX10Render::DX10Render(core::Root &parent, graphics::RenderCreationParams &params, core::NativeWindow *outputWindow) : graphics::RenderAPI(parent)
{
	HRESULT result;
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	//IDXGIFactory *dxfactory;
	ID3D10Texture2D *backBuffer, *depthStencilBuffer;

	//HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&dxfactory);

	//result = (D3D10CreateDevice(NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, 0, D3D10_SDK_VERSION, &this->device));
	//ASSERT(result == S_OK);

	// Create swap chain and device
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = params.backBufferSize.x;
	swapChainDesc.BufferDesc.Height = params.backBufferSize.y;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // TODO: RenderCreationParams enum!
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.OutputWindow = outputWindow->getHandle();
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.SampleDesc.Count = params.multisampleCount;
	swapChainDesc.SampleDesc.Quality = params.multisampleQuality;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Windowed = TRUE; // TODO: Should not always be true!

	core::U32_t flags = 0;
#if defined(VTX_DEBUG)
	flags |= D3D10_CREATE_DEVICE_DEBUG;
#endif
	result = D3D10CreateDeviceAndSwapChain(NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, flags, D3D10_SDK_VERSION, &swapChainDesc, &this->swapChain, &this->device);
	//result = dxfactory->CreateSwapChain(this->device, &swapChainDesc, &this->swapChain);
	ASSERT(result == S_OK);

	// Create render target view.
	result = this->swapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), reinterpret_cast<void**>(&backBuffer));
	ASSERT(result == S_OK);

	result = device->CreateRenderTargetView(backBuffer, NULL, &renderTargetView);
	ASSERT(result == S_OK);

	ReleaseCOM(backBuffer);

	// Create depth/stencil buffer/view.

	D3D10_TEXTURE2D_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(D3D10_TEXTURE2D_DESC));
	depthStencilDesc.Width = params.backBufferSize.x;
	depthStencilDesc.Height = params.backBufferSize.y;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.BindFlags = D3D10_BIND_DEPTH_STENCIL;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;
	depthStencilDesc.SampleDesc.Count = params.multisampleCount;
	depthStencilDesc.SampleDesc.Quality = params.multisampleQuality;
	depthStencilDesc.Usage = D3D10_USAGE_DEFAULT;

	result = device->CreateTexture2D(&depthStencilDesc, NULL, &depthStencilBuffer);
	ASSERT(result == S_OK);

	ID3D10DepthStencilView *depthStencilView;
	result = device->CreateDepthStencilView(depthStencilBuffer, NULL, &depthStencilView);
	ASSERT(result == S_OK);

	// Bind render target view and depth stencil view.
	device->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

	// Set viewport
	// TODO: Viewport might not always occupy entire screen!
	D3D10_VIEWPORT vp;
	vp.Width = params.backBufferSize.x;
	vp.Height = params.backBufferSize.y;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	device->RSSetViewports( 1, &vp );

}

void graphics::DX10Render::clear()
{
	this->device->ClearRenderTargetView(this->renderTargetView, this->clearColor.values);
}

void graphics::DX10Render::swap(void)
{
	HRESULT result = this->swapChain->Present(0, 0);
	ASSERT(result == S_OK);
}

graphics::VertexBuffer *graphics::DX10Render::createVertexBuffer(graphics::VertexPosNormTex *vertices, core::U32_t noVertices, graphics::E_BUFFER_USAGE usage)
{
	D3D10_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(D3D10_BUFFER_DESC));
	bufferDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	bufferDesc.ByteWidth = sizeof(VertexPosNormTex) * noVertices; // TODO: How to handle other vertex types?
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	switch(usage)
	{
	case E_BUFFER_USAGE_DYNAMIC:
		bufferDesc.Usage = D3D10_USAGE_DYNAMIC;
		break;
	case E_BUFFER_USAGE_IMMUTABLE:
		bufferDesc.Usage = D3D10_USAGE_IMMUTABLE;
		break;
	}

	D3D10_SUBRESOURCE_DATA subresData;
	ZeroMemory(&subresData, sizeof(D3D10_SUBRESOURCE_DATA));
	subresData.pSysMem = vertices;

	ID3D10Buffer *vertexBuffer;
	core::U32_t result = this->device->CreateBuffer(&bufferDesc, &subresData, &vertexBuffer);
	ASSERT(result == S_OK);

	return new DX10VertexBuffer(vertexBuffer);
}

void graphics::DX10Render::bindVertexBuffers(core::U32_t slot, core::U32_t bufferCount, graphics::VertexBuffer **buffers, const core::U32_t *strides, const core::U32_t *offsets)
{
	// Only allow 1 VertexBuffer to be bound for time being. I have to figure out how to design the VertexBuffer general structure.
	DX10VertexBuffer *vb = reinterpret_cast<DX10VertexBuffer*>(buffers[0]);
	this->device->IASetVertexBuffers(slot, bufferCount, &vb->buffer, strides, offsets);
}

void graphics::DX10Render::draw(core::U32_t verticeCount, core::U32_t startVertex)
{
	this->device->Draw(verticeCount, startVertex);
}

void graphics::DX10Render::setPrimitiveType(graphics::E_PRIMITIVE_TYPE type)
{
	ASSERT(type >= 0);	// check against minimum value
	ASSERT(type < 9);	// check against maximum value
	switch(type)
	{
	case E_PRIMITIVE_LINELIST:
		this->device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINELIST);
		break;
	case E_PRIMITIVE_LINELIST_ADJ:
		this->device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINELIST_ADJ);
		break;
	case E_PRIMITIVE_LINESTRIP:
		this->device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP);
		break;
	case E_PRIMITIVE_LINESTRIP_ADJ:
		this->device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ);
		break;
	case E_PRIMITIVE_POINTLIST:
		this->device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_POINTLIST);
		break;
	case E_PRIMITIVE_TRIANGLELIST:
		this->device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		break;
	case E_PRIMITIVE_TRIANGLELIST_ADJ:
		this->device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ);
		break;
	case E_PRIMITIVE_TRIANGLESTRIP:
		this->device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		break;
	case E_PRIMITIVE_TRIANGLESTRIP_ADJ:
		this->device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ);
		break;
	}
}

#endif
