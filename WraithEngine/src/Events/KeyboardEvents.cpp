#include "wrpch.h"
#include "KeyboardEvents.h"

namespace Wraith
{
#pragma region KeyPressedEvent

	KeyPressedEvent::KeyPressedEvent(unsigned char keyCode)
		: _keyCode(keyCode)
	{}

	EventType KeyPressedEvent::GetType() const
	{
		return static_cast<EventType>(KeyboardEventType::KeyPressed);
	}

	std::string KeyPressedEvent::ToString() const
	{
		std::ostringstream oss;
		oss << "KeyPressedEvent: " << _keyCode;
		return oss.str();
	}

	unsigned char KeyPressedEvent::GetKeyCode() const
	{
		return _keyCode;
	}

#pragma endregion

#pragma region KeyReleasedEvent

	KeyReleasedEvent::KeyReleasedEvent(unsigned char keyCode)
		: _keyCode(keyCode)
	{}

	EventType KeyReleasedEvent::GetType() const
	{
		return static_cast<EventType>(KeyboardEventType::KeyReleased);
	}

	std::string KeyReleasedEvent::ToString() const
	{
		std::ostringstream oss;
		oss << "KeyReleasedEvent: " << _keyCode;
		return oss.str();
	}

	unsigned char KeyReleasedEvent::GetKeyCode() const
	{
		return _keyCode;
	}

#pragma endregion

#pragma region KeyTypedEvent

	KeyTypedEvent::KeyTypedEvent(char character)
		: _character(character)
	{}

	EventType KeyTypedEvent::GetType() const
	{
		return static_cast<EventType>(KeyboardEventType::KeyTyped);
	}

	std::string KeyTypedEvent::ToString() const
	{
		std::ostringstream oss;
		oss << "KeyTypedEvent: " << _character;
		return oss.str();
	}

	char KeyTypedEvent::GetChar() const
	{
		return _character;
	}

#pragma endregion 
}

