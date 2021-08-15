#include "wrpch.h"

#include "Input.h"
#include "Events/EventBus.h"

namespace Wraith
{
	void Input::Init()
	{	
		EventBus::Register<MouseMovedEvent>(WR_BIND_EVENT_CALLBACK_STATIC(OnMouseMoved));
		EventBus::Register<MouseButtonPressedEvent>(WR_BIND_EVENT_CALLBACK_STATIC(OnMouseButtonPressed));
		EventBus::Register<MouseButtonReleasedEvent>(WR_BIND_EVENT_CALLBACK_STATIC(OnMouseButtonReleased));
		EventBus::Register<MouseWheelDeltaEvent>(WR_BIND_EVENT_CALLBACK_STATIC(OnMouseWheelDelta));

		EventBus::Register<KeyPressedEvent>(WR_BIND_EVENT_CALLBACK_STATIC(OnKeyPressed));
		EventBus::Register<KeyReleasedEvent>(WR_BIND_EVENT_CALLBACK_STATIC(OnKeyReleased));
		EventBus::Register<KeyTypedEvent>(WR_BIND_EVENT_CALLBACK_STATIC(OnKeyTyped));
	}

#pragma region Mouse Input
	
	int Input::s_xPos = 0;
	int Input::s_yPos = 0;
	int Input::s_wheelDelta = 0;
	bool Input::s_isInWindow = false;
	std::bitset<static_cast<size_t>(MouseButton::Count)> Input::s_mouseButtonStates;

	void Input::OnMouseMoved(const MouseMovedEvent& event)
	{
		s_xPos = event.GetXPos();
		s_yPos = event.GetYPos();
	}

	void Input::OnMouseButtonPressed(const MouseButtonPressedEvent& event)
	{
		s_mouseButtonStates[static_cast<int>(event.GetButton())] = true;
	}

	void Input::OnMouseButtonReleased(const MouseButtonReleasedEvent& event)
	{
		s_mouseButtonStates[static_cast<int>(event.GetButton())] = false;
	}

	void Input::OnMouseWheelDelta(const MouseWheelDeltaEvent& event)
	{
		s_wheelDelta = event.GetDelta();
	}

#pragma endregion

#pragma region Keyboard Input

	std::bitset<Input::NUM_KEYS> Input::s_keyStates;
	std::queue<char> Input::s_charsTyped;

	void Input::OnKeyPressed(const KeyPressedEvent& event)
	{
		s_keyStates[event.GetKeyCode()] = true;
	}

	void Input::OnKeyReleased(const KeyReleasedEvent& event)
	{
		s_keyStates[event.GetKeyCode()] = false;
	}

	void Input::OnKeyTyped(const KeyTypedEvent& event)
	{
		s_charsTyped.push(event.GetChar());
	}
	
#pragma endregion 
	
}
