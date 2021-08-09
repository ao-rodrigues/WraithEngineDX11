#include "wrpch.h"
#include "Core/MouseCodes.h"
#include "MouseEvents.h"

namespace Wraith
{
#pragma region MouseButtonPressedEvent
	
	MouseButtonPressedEvent::MouseButtonPressedEvent(MouseButton button)
		: _button(button)
	{}

	EventType MouseButtonPressedEvent::GetType() const
	{
		return static_cast<EventType>(MouseEventType::ButtonPressed);
	}

	std::string MouseButtonPressedEvent::ToString() const
	{
		std::ostringstream oss;
		oss << "MouseButtonPressedEvent: " << static_cast<int>(_button);
		return oss.str();
	}

	MouseButton MouseButtonPressedEvent::GetButton() const
	{
		return _button;
	}

#pragma endregion

#pragma region MouseButtonReleasedEvent
	
	MouseButtonReleasedEvent::MouseButtonReleasedEvent(MouseButton button)
		:_button(button)
	{}

	EventType MouseButtonReleasedEvent::GetType() const
	{
		return static_cast<EventType>(MouseEventType::ButtonReleased);
	}

	std::string MouseButtonReleasedEvent::ToString() const
	{
		std::ostringstream oss;
		oss << "MouseButtonReleasedEvent: " << static_cast<int>(_button);
		return oss.str();
	}

	MouseButton MouseButtonReleasedEvent::GetButton() const
	{
		return _button;
	}

#pragma endregion

#pragma region MouseWheelDeltaEvent
	
	MouseWheelDeltaEvent::MouseWheelDeltaEvent(int delta)
		: _delta(delta)
	{}

	EventType MouseWheelDeltaEvent::GetType() const
	{
		return static_cast<EventType>(MouseEventType::WheelDelta);
	}

	std::string MouseWheelDeltaEvent::ToString() const
	{
		std::ostringstream oss;
		oss << "MouseWheelDeltaEvent: " << _delta;
		return oss.str();
	}

	int MouseWheelDeltaEvent::GetDelta() const
	{
		return _delta;
	}

#pragma endregion

#pragma region MouseMovedEvent

	MouseMovedEvent::MouseMovedEvent(int x, int y)
		: _x(x)
		, _y(y)
	{}

	EventType MouseMovedEvent::GetType() const
	{
		return static_cast<EventType>(MouseEventType::Moved);
	}

	std::string MouseMovedEvent::ToString() const
	{
		std::ostringstream oss;
		oss << "MouseMovedEvent: " << "(" << _x << "," << _y << ")";
		return oss.str();
	}

	int MouseMovedEvent::GetXPos() const
	{
		return _x;
	}

	int MouseMovedEvent::GetYPos() const
	{
		return _y;
	}

#pragma endregion

#pragma region MouseEnterEvent
	
	EventType MouseEnterEvent::GetType() const
	{
		return static_cast<EventType>(MouseEventType::Enter);
	}

	std::string MouseEnterEvent::ToString() const
	{
		std::ostringstream oss;
		oss << "MouseEnterEvent";
		return oss.str();
	}

#pragma endregion

#pragma region MouseLeaveEvent

	EventType MouseLeaveEvent::GetType() const
	{
		return static_cast<EventType>(MouseEventType::Leave);
	}

	std::string MouseLeaveEvent::ToString() const
	{
		std::ostringstream oss;
		oss << "MouseLeaveEvent";
		return oss.str();
	}
	
#pragma endregion 
}
