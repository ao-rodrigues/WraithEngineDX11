#pragma once
#include "Renderer/RendererAPI.h"
#include "Platform/Windows/Win32Exception.h"

struct ID3D11Device;
struct IDXGISwapChain;
struct ID3D11DeviceContext;
struct ID3D11RenderTargetView;

namespace Wraith
{
	class DirectX11RendererAPI : public RendererAPI
	{
	public:
		DirectX11RendererAPI(HWND windowHandle);
		~DirectX11RendererAPI() override;
		
		void Init() override;
		void SetClearColor(float red, float green, float blue, float alpha) override;
		void DrawTestTriangles() override;
		void SwapBuffers() override;

	private:
		HWND _windowHandle;
		ID3D11Device* _device = nullptr;
		IDXGISwapChain* _swapChain = nullptr;
		ID3D11DeviceContext* _context = nullptr;
		ID3D11RenderTargetView* _renderTargetView = nullptr;
	};

	class DeviceRemovedException : public Win32Exception
	{
	public:
		DeviceRemovedException(int line, const char* file, HRESULT hr)
			: Win32Exception(line, file, hr)
		{}

		const char* GetType() const noexcept override
		{
			return "Device Removed Exception";
		}
	};

#define WRAITH_DEVICE_REMOVED(hr) DeviceRemovedException(__LINE__, __FILE__, hr)
}
