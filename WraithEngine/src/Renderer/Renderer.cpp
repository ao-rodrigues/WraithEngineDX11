#include "wrpch.h"
#include "Renderer.h"
#include "RendererAPI.h"

namespace Wraith
{
	std::unique_ptr<RendererAPI> Renderer::s_rendererAPI;
	
	void Renderer::Init(void* windowHandle)
	{
		s_rendererAPI = RendererAPI::Create(windowHandle);
		s_rendererAPI->Init();
	}

	void Renderer::Shutdown()
	{
	}

	void Renderer::SetClearColor(float red, float green, float blue, float alpha)
	{
		s_rendererAPI->SetClearColor(red, green, blue, alpha);
	}

	void Renderer::Render()
	{
		s_rendererAPI->DrawTestTriangles();
		s_rendererAPI->SwapBuffers();
	}
}
