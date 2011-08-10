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
#include <platform/vtx_defineconfig.h>
#include <vortex/vtx_dx10render.h>
#include <core/vtx_assertions.h>

#if defined(VTX_PLATFORM_WIN32) && defined(VTX_COMPILE_WITH_DX10)

// This class is not exposed as it is not intended to be used directly.
class DX10VertexBuffer : public VertexBuffer
{
private:
	ID3D10Buffer *buffer;
public:
	DX10VertexBuffer(ID3D10Buffer *d3dbuffer)
		: buffer(d3dbuffer)
	{
	}
};

using namespace platform;

DX10Render::DX10Render(Root &parent, RenderCreationParams &params, NativeWindow *outputWindow) : RenderAPI(parent)
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

	platform::U32_t flags = 0;
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

void DX10Render::clear()
{
	this->device->ClearRenderTargetView(this->renderTargetView, this->clearColor.values);
}

void DX10Render::swap(void)
{
	HRESULT result = this->swapChain->Present(0, 0);
	ASSERT(result == S_OK);
}

VertexBuffer *DX10Render::createVertexBuffer(VertexPosNormTex *vertices, platform::U32_t noVertices, E_BUFFER_USAGE usage)
{
	D3D10_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(D3D10_BUFFER_DESC));
	bufferDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	bufferDesc.ByteWidth = sizeof(VertexPosNormTex) * noVertices; // TODO: How to handle other vertex types?
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	switch(usage)
	{
	case BUFFER_USAGE_DYNAMIC:
		bufferDesc.Usage = D3D10_USAGE_DYNAMIC;
		break;
	case BUFFER_USAGE_IMMUTABLE:
		bufferDesc.Usage = D3D10_USAGE_IMMUTABLE;
		break;
	}

	D3D10_SUBRESOURCE_DATA subresData;
	ZeroMemory(&subresData, sizeof(D3D10_SUBRESOURCE_DATA));
	subresData.pSysMem = vertices;

	ID3D10Buffer *vertexBuffer;
	platform::U32_t result = this->device->CreateBuffer(&bufferDesc, &subresData, &vertexBuffer);
	ASSERT(result == S_OK);

	return new DX10VertexBuffer(vertexBuffer);
}

void DX10Render::bindVertexBuffers(platform::U32_t slot, platform::U32_t bufferCount, VertexBuffer **buffers, const platform::U32_t *strides, const platform::U32_t *offsets)
{
	this->device->IASetVertexBuffers(slot, bufferCount, reinterpret_cast<ID3D10Buffer**>(buffers), strides, offsets);
}

void DX10Render::draw(platform::U32_t verticeCount, platform::U32_t startVertex)
{
	this->device->Draw(verticeCount, startVertex);
}

#endif
