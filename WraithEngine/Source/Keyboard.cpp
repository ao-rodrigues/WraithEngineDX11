#include "pch.h"
#include "Keyboard.h"

using namespace Wraith;

bool Keyboard::KeyIsPressed(unsigned char keyCode) const noexcept
{
	return _keyStates[keyCode];
}

std::optional<Keyboard::KeyEvent> Keyboard::GetKeyEvent() noexcept
{
	if(!_keyEvents.empty())
	{
		const KeyEvent e = _keyEvents.front();
		_keyEvents.pop();
		return e;
	}

	return {};
}

bool Keyboard::HasKeyEvents() const noexcept
{
	return !_keyEvents.empty();
}

void Keyboard::ClearKeyEvents() noexcept
{
	_keyEvents = std::queue<KeyEvent>();
}

std::optional<char> Keyboard::ReadChar() noexcept
{
	if(!_charEvents.empty())
	{
		unsigned char charCode = _charEvents.front();
		_charEvents.pop();
		return charCode;
	}

	return {};
}

bool Keyboard::HasCharEvents() const noexcept
{
	return !_charEvents.empty();
}

void Keyboard::ClearCharEvents() noexcept
{
	_charEvents = std::queue<char>();
}

void Keyboard::ClearAllEvents() noexcept
{
	ClearKeyEvents();
	ClearCharEvents();
}

void Keyboard::EnableAutoRepeat() noexcept
{
	_autoRepeatEnabled = true;
}

void Keyboard::DisableAutoRepeat() noexcept
{
	_autoRepeatEnabled = false;
}

bool Keyboard::AutoRepeatIsEnabled() const noexcept
{
	return _autoRepeatEnabled;
}

void Keyboard::OnKeyPressed(unsigned char keyCode) noexcept
{
	_keyStates[keyCode] = true;
	_keyEvents.push(KeyEvent(KeyEvent::Type::Press, keyCode));
	TrimEventQueue(_keyEvents);
}

void Keyboard::OnKeyReleased(unsigned char keyCode) noexcept
{
	_keyStates[keyCode] = false;
	_keyEvents.push(KeyEvent(KeyEvent::Type::Release, keyCode));
	TrimEventQueue(_keyEvents);
}

void Keyboard::OnChar(char character) noexcept
{
	_charEvents.push(character);
	TrimEventQueue(_charEvents);
}

void Keyboard::ClearKeyStates() noexcept
{
	_keyStates.reset();
}

template <typename T>
void Keyboard::TrimEventQueue(std::queue<T>& eventQueue) noexcept
{
	while (eventQueue.size() > EVENT_QUEUE_SIZE)
	{
		eventQueue.pop();
	}
}
