#include "wrpch.h"

#include "Application.h"
#include "Input.h"
#include "Logger.h"
#include "Renderer/Renderer.h"

namespace Wraith
{
	Application::Application(const std::string& name, int windowWidth, int windowHeight)
		: _window(Window::Create(name, windowWidth, windowHeight))
	{
		Input::Init();
		Renderer::Init(_window->GetWindowHandle());
	}

	int Application::Run()
	{
		WR_LOG_INFO("Client initialized!");
		
		while (true)
		{
			if(const auto exitCode = _window->ProcessMessages())
			{
				Shutdown();
				return *exitCode;
			}

			Renderer::SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			Renderer::Render();
		}
	}

	void Application::Shutdown()
	{
		Renderer::Shutdown();
	}
}

