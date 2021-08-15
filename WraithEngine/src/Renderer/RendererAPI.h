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

		class Exception : public WraithException
		{
		public:
			Exception(int line, const char* file, API renderingAPI);
			const char* what() const noexcept override;
			const char* GetType() const noexcept override;
			std::string GetErrorString() const;
		private:
			API _renderingAPI;
		};
		
		virtual ~RendererAPI() = default;
		
		virtual void Init() = 0;
		virtual void SetClearColor(float red, float green, float blue, float alpha) = 0;
		virtual void SwapBuffers() = 0;

		static std::unique_ptr<RendererAPI> Create(void* windowHandle);

	private:
		static API s_API;
	};

#define WR_RENDERER_API_EXCEPTION(api) RendererAPI::Exception(__LINE__, __FILE__, api)
}
