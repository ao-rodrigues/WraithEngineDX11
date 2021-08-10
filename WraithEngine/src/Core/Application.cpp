#include "wrpch.h"

#include "Application.h"
#include "Input.h"
#include "Logger.h"
#include "Events/EventBus.h"
#include "Events/Event.h"
#include "Events/MouseEvents.h"
#include "Events/KeyboardEvents.h"
#include "Core/KeyCodes.h"

namespace Wraith
{
	Application::Application(const std::string& name, int windowWidth, int windowHeight)
		: _window(Window::Create(name, windowWidth, windowHeight))
	{
		Input::Init();
	}

	int Application::Run()
	{
		WR_LOG_INFO("Client initialized!");

		EventBus::Register<MouseButtonPressedEvent>([](const MouseButtonPressedEvent& event)
		{
			WR_LOG_INFO("Pressed Mouse Button {0}", event.GetButton());
		});

		EventBus::Register<MouseButtonReleasedEvent>([](const MouseButtonReleasedEvent& event)
		{
			WR_LOG_INFO("Released Mouse Button {0}", event.GetButton());
		});

		EventBus::Register<MouseMovedEvent>([](const MouseMovedEvent& event)
		{
			WR_LOG_TRACE("Mouse Position: ({0},{1})", event.GetXPos(), event.GetYPos());
		});
		
		while (true)
		{
			if(const auto exitCode = _window->ProcessMessages())
			{
				return *exitCode;
			}

			if (Input::IsKeyDown(KeyCode::A))
			{
				WR_LOG_WARN("aaaaaaaaaaaaaaaaaaaa");
			}
		}
	}
}

