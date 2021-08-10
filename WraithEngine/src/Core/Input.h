#pragma once

#include "MouseCodes.h"
#include "Events/MouseEvents.h"
#include "Events/KeyboardEvents.h"
#include "KeyCodes.h"

namespace Wraith
{	
	class Input
	{
	friend class Application;
#ifdef WR_PLATFORM_WINDOWS
	friend class Win32Window;
#endif
	public:
		static int GetMousePosX() { return s_xPos; }
		static int GetMousePosY() { return s_yPos; }
		static int GetMouseWheelDelta() { return s_wheelDelta; }
		static bool IsMouseButtonDown(MouseButton button) { return s_mouseButtonStates[static_cast<int>(button)]; }
		static bool IsMouseInWindow() { return s_isInWindow; }

		static bool IsKeyDown(KeyCode keyCode) { return s_keyStates[static_cast<unsigned char>(keyCode)]; }
		static std::optional<char> ReadChar()
		{
			if (!s_charsTyped.empty())
			{
				const auto charCode = s_charsTyped.front();
				s_charsTyped.pop();
				return charCode;
			}

			return {};
		}

	private:
		static void Init();

		static void OnMouseMoved(const MouseMovedEvent& event);
		static void OnMouseButtonPressed(const MouseButtonPressedEvent& event);
		static void OnMouseButtonReleased(const MouseButtonReleasedEvent& event);
		static void OnMouseWheelDelta(const MouseWheelDeltaEvent& event);

		static int s_xPos;
		static int s_yPos;
		static int s_wheelDelta;
		static bool s_isInWindow;
		static std::bitset<static_cast<size_t>(MouseButton::Count)> s_mouseButtonStates;

		static void OnKeyPressed(const KeyPressedEvent& event);
		static void OnKeyReleased(const KeyReleasedEvent& event);
		static void OnKeyTyped(const KeyTypedEvent& event);
		static void ClearKeyStates() { s_keyStates.reset(); }

		static constexpr unsigned int NUM_KEYS = 256u;
		static std::bitset<NUM_KEYS> s_keyStates;
		static std::queue<char> s_charsTyped;
	};	
}
