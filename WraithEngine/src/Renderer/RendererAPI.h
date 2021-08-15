#pragma once
#include "Core/WraithException.h"

namespace Wraith
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0,
			DirectX11,
			DirectX12,
			Vulkan
			// Future APIs here...
		};
		
		virtual ~RendererAPI() = default;
		
		virtual void Init() = 0;
		virtual void SetClearColor(float red, float green, float blue, float alpha) = 0;
		virtual void SwapBuffers() = 0;

		static std::unique_ptr<RendererAPI> Create(void* windowHandle);

	private:
		static API s_API;
	};

	class UnsupportedAPIException : public WraithException
	{
	public:
		UnsupportedAPIException(int line, const char* file, RendererAPI::API renderingAPI);
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		std::string GetErrorString() const;
	private:
		RendererAPI::API _renderingAPI;
	};

#define WR_RENDERER_API_EXCEPTION(api) UnsupportedAPIException(__LINE__, __FILE__, api)
}
