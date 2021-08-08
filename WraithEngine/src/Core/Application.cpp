#include "wrpch.h"

#include "Application.h"

namespace Wraith
{
	Application::Application(const std::string& name, int windowWidth, int windowHeight)
		: _window(Window::Create(name, windowWidth, windowHeight))
	{}

	int Application::Run()
	{
		while (true)
		{
			if(const auto exitCode = _window->ProcessMessages())
			{
				return *exitCode;
			}
		}
	}
}

