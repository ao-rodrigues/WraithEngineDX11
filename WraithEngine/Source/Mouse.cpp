#include "pch.h"
#include "Mouse.h"

using namespace Wraith;

std::pair<int, int> Mouse::GetPos() const noexcept
{
	return {_x, _y};
}

int Mouse::GetPosX() const noexcept
{
	return _x;
}

int Mouse::GetPosY() const noexcept
{
	return _y;
}

bool Mouse::IsInWindow() const noexcept
{
	return _isInWindow;
}

bool Mouse::LeftIsPressed() const noexcept
{
	return _leftIsPressed;
}

bool Mouse::RightIsPressed() const noexcept
{
	return _rightIsPressed;
}

std::optional<Mouse::MouseEvent> Mouse::GetMouseEvent() noexcept
{
	if(!_mouseEvents.empty())
	{
		const auto e = _mouseEvents.front();
		_mouseEvents.pop();

		return e;
	}

	return {};
}

void Mouse::ClearMouseEvents() noexcept
{
	_mouseEvents = std::queue<MouseEvent>();
}

void Mouse::OnMouseMove(int x, int y) noexcept
{
	SetPos(x, y);

	_mouseEvents.push(MouseEvent(MouseEvent::Type::Move, *this));
	TrimEventQueue();
}

void Mouse::OnMouseEnter() noexcept
{
	_isInWindow = true;
	_mouseEvents.push(MouseEvent(MouseEvent::Type::Enter, *this));
	TrimEventQueue();
}

void Mouse::OnMouseLeave() noexcept
{
	_isInWindow = false;
	_mouseEvents.push(MouseEvent(MouseEvent::Type::Leave, *this));
	TrimEventQueue();
}

void Mouse::OnLeftPressed(int x, int y) noexcept
{
	SetPos(x, y);

	_leftIsPressed = true;
	_mouseEvents.push(MouseEvent(MouseEvent::Type::LPress, *this));
	TrimEventQueue();
}

void Mouse::OnLeftReleased(int x, int y) noexcept
{
	SetPos(x, y);

	_leftIsPressed = false;
	_mouseEvents.push(MouseEvent(MouseEvent::Type::LRelease, *this));
	TrimEventQueue();
}

void Mouse::OnRightPressed(int x, int y) noexcept
{
	SetPos(x, y);

	_rightIsPressed = true;
	_mouseEvents.push(MouseEvent(MouseEvent::Type::RPress, *this));
	TrimEventQueue();
}

void Mouse::OnRightReleased(int x, int y) noexcept
{
	SetPos(x, y);

	_rightIsPressed = false;
	_mouseEvents.push(MouseEvent(MouseEvent::Type::RRelease, *this));
	TrimEventQueue();
}

void Mouse::OnWheelUp(int x, int y) noexcept
{
	SetPos(x, y);

	_mouseEvents.push(MouseEvent(MouseEvent::Type::WheelUp, *this));
	TrimEventQueue();
}

void Mouse::OnWheelDown(int x, int y) noexcept
{
	SetPos(x, y);

	_mouseEvents.push(MouseEvent(MouseEvent::Type::WheelDown, *this));
	TrimEventQueue();
}

void Mouse::OnWheelDelta(int x, int y, int delta) noexcept
{
	_accumulatedWheelDelta += delta;

	// Generate wheel events for every 120
	while(_accumulatedWheelDelta >= WHEEL_DELTA)
	{
		_accumulatedWheelDelta -= WHEEL_DELTA;
		OnWheelUp(x, y);
	}

	while (_accumulatedWheelDelta <= -WHEEL_DELTA)
	{
		_accumulatedWheelDelta += WHEEL_DELTA;
		OnWheelDown(x, y);
	}
}

void Mouse::TrimEventQueue() noexcept
{
	while (_mouseEvents.size() > EVENT_QUEUE_SIZE)
	{
		_mouseEvents.pop();
	}
}

void Mouse::SetPos(int x, int y) noexcept
{
	_x = x;
	_y = y;
}

