#pragma once
#include "Renderer/RendererAPI.h"

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
		void SwapBuffers() override;

	private:
		HWND _windowHandle;
		ID3D11Device* _device = nullptr;
		IDXGISwapChain* _swapChain = nullptr;
		ID3D11DeviceContext* _context = nullptr;
		ID3D11RenderTargetView* _renderTargetView = nullptr;
	};
}
