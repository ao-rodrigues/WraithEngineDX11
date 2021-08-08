#pragma once
#include "Event.h"

namespace Wraith
{
	enum class KeyboardEventType
	{
		KeyPressed,
		KeyReleased,
		KeyTyped
	};

	class KeyPressedEvent : public Event
	{
	public:
		KeyPressedEvent(unsigned char keyCode);

		EventType GetType() const override;
		std::string ToString() const override;

		unsigned char GetKeyCode() const;
	private:
		unsigned char _keyCode;
	};

	class KeyReleasedEvent : public Event
	{
	public:
		KeyReleasedEvent(unsigned char keyCode);

		EventType GetType() const override;
		std::string ToString() const override;

		unsigned char GetKeyCode() const;
	private:
		unsigned char _keyCode;
	};

	class KeyTypedEvent : public Event
	{
	public:
		KeyTypedEvent(char character);

		EventType GetType() const override;
		std::string ToString() const override;

		char GetChar() const;
	private:
		char _character;
	};
}

