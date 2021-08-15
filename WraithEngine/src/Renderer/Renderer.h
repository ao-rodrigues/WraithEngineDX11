#pragma once


namespace Wraith
{
	class RendererAPI;
	
	class Renderer
	{
	public:
		static void Init(void* windowHandle);
		static void Shutdown();

		static void SetClearColor(float red, float green, float blue, float alpha);
		static void Render();
	
	private:
		static std::unique_ptr<RendererAPI> s_rendererAPI;
	};
}
