#pragma once

#include "Event.h"

namespace Wraith
{
	enum class MouseEventType
	{
		ButtonPressed = 0,
		ButtonReleased,
		WheelDelta,
		Moved,
		Enter,
		Leave
	};

	enum class MouseButton
	{
		Left = 0,
		Right,
		Middle
	};

	class MouseButtonPressedEvent : public Event
	{
	public:
		MouseButtonPressedEvent(MouseButton button);
		
		EventType GetType() const override;
		std::string ToString() const override;
		
		MouseButton GetButton() const;

	private:
		MouseButton _button;
	};

	class MouseButtonReleasedEvent : public Event
	{
	public:
		MouseButtonReleasedEvent(MouseButton button);

		EventType GetType() const override;
		std::string ToString() const override;
		
		MouseButton GetButton() const;
	
	private:
		MouseButton _button;
	};

	class MouseWheelDeltaEvent : public Event
	{
	public:
		MouseWheelDeltaEvent(int delta);
		
		EventType GetType() const override;
		std::string ToString() const override;

		int GetDelta() const;

	private:
		int _delta;
	};

	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(int x, int y);

		EventType GetType() const override;
		std::string ToString() const override;

		int GetXPos() const;
		int GetYPos() const;
	
	private:
		int _x;
		int _y;
	};

	class MouseEnterEvent : public Event
	{
	public:
		MouseEnterEvent() = default;
		
		EventType GetType() const override;
		std::string ToString() const override;
	};

	class MouseLeaveEvent : public Event
	{
	public:
		MouseLeaveEvent() = default;
		
		EventType GetType() const override;
		std::string ToString() const override;
	};
}
