#pragma once

#include "Core/Base.h"
#include "Core/Window.h"

namespace Wraith
{
	class Application
	{
	public:
		Application(const std::string& name = "Wraith App", int windowWidth = 1280, int windowHeight = 720);
		virtual ~Application() = default;

		int Run();

	private:
		std::shared_ptr<Window> _window;
	};

	// To be defined by Client
	Application CreateApplication();
}
