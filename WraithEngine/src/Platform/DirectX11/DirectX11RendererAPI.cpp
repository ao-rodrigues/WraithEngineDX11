#include "wrpch.h"
#include "DirectX11RendererAPI.h"
#include "DirectX11Exception.h"

#include <d3d11.h>

namespace Wraith
{
	DirectX11RendererAPI::DirectX11RendererAPI(HWND windowHandle)
		:_windowHandle(windowHandle)
	{}

	DirectX11RendererAPI::~DirectX11RendererAPI()
	{
		if (_swapChain)
		{
			_swapChain->Release();
		}

		if (_device)
		{
			_device->Release();
		}

		if (_context)
		{
			_context->Release();
		}
	}

	void DirectX11RendererAPI::Init()
	{
		DXGI_SWAP_CHAIN_DESC sd = {};
		sd.BufferDesc.Width = 0;
		sd.BufferDesc.Height = 0;
		sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 0;
		sd.BufferDesc.RefreshRate.Denominator = 0;
		sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferCount = 1;
		sd.OutputWindow = _windowHandle;
		sd.Windowed = TRUE;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		sd.Flags = 0;

		UINT creationFlags = 0;
#ifdef WRAITH_DEBUG
		creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
		
		HRESULT hr;
		WRAITH_DX11_ERROR_CHECK(D3D11CreateDeviceAndSwapChain(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			creationFlags,
			nullptr,
			0,
			D3D11_SDK_VERSION,
			&sd,
			&_swapChain,
			&_device,
			nullptr,
			&_context
		));

		ID3D11Resource* backBuffer = nullptr;
		WRAITH_DX11_ERROR_CHECK(_swapChain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&backBuffer)));
		WRAITH_DX11_ERROR_CHECK(_device->CreateRenderTargetView(
			backBuffer,
			nullptr,
			&_renderTargetView
		));
		backBuffer->Release();
	}

	void DirectX11RendererAPI::SetClearColor(float red, float green, float blue, float alpha)
	{
		const float color[] = {red, green, blue, alpha};
		_context->ClearRenderTargetView(_renderTargetView, color);
	}

	void DirectX11RendererAPI::SwapBuffers()
	{
		HRESULT hr;
		if(FAILED(hr =_swapChain->Present(1u, 0u)))
		{
			if (hr == DXGI_ERROR_DEVICE_REMOVED)
			{
				throw WRAITH_DEVICE_REMOVED(_device->GetDeviceRemovedReason());
			}
			
			WRAITH_DX11_ERROR_CHECK(hr);
		}
	}
}
