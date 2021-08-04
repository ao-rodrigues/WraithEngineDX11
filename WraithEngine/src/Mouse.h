#pragma once

namespace Wraith
{
	class Mouse
	{
		friend class Window;
	public:
		class MouseEvent
		{
		public:
			enum class Type
			{
				LPress,
				LRelease,
				RPress,
				RRelease,
				WheelUp,
				WheelDown,
				Move,
				Enter,
				Leave
			};

			MouseEvent(Type type, const Mouse& parent) noexcept
				: _type(type)
				, _leftIsPressed(parent.LeftIsPressed())
				, _rightIsPressed(parent.RightIsPressed())
				, _x(parent.GetPosX())
				, _y(parent.GetPosY())
			{}

			Type GetType() const noexcept
			{
				return _type;
			}

			std::pair<int, int> GetPos() const noexcept
			{
				return {_x, _y};
			}

			int GetPosX() const noexcept
			{
				return _x;
			}

			int GetPosY() const noexcept
			{
				return _y;
			}

			bool LeftIsPressed() const noexcept
			{
				return _leftIsPressed;
			}

			bool RightIsPressed() const noexcept
			{
				return _rightIsPressed;
			}

		private:
			Type _type;
			bool _leftIsPressed;
			bool _rightIsPressed;
			int _x;
			int _y;
		};

		Mouse() = default;
		Mouse(const Mouse&) = delete;
		Mouse& operator=(const Mouse&) = delete;

		std::pair<int, int> GetPos() const noexcept;
		int GetPosX() const noexcept;
		int GetPosY() const noexcept;
		bool IsInWindow() const noexcept;
		bool LeftIsPressed() const noexcept;
		bool RightIsPressed() const noexcept;
		std::optional<MouseEvent> GetMouseEvent() noexcept;
		bool HasMouseEvents() const noexcept
		{
			return !_mouseEvents.empty();
		}
		void ClearMouseEvents() noexcept;

	private:
		void OnMouseMove(int x, int y) noexcept;
		void OnMouseEnter() noexcept;
		void OnMouseLeave() noexcept;
		void OnLeftPressed(int x, int y) noexcept;
		void OnLeftReleased(int x, int y) noexcept;
		void OnRightPressed(int x, int y) noexcept;
		void OnRightReleased(int x, int y) noexcept;
		void OnWheelUp(int x, int y) noexcept;
		void OnWheelDown(int x, int y) noexcept;
		void OnWheelDelta(int x, int y, int delta) noexcept;
		void TrimEventQueue() noexcept;
		void SetPos(int x, int y) noexcept;

		static constexpr unsigned int EVENT_QUEUE_SIZE = 16u;
		int _x;
		int _y;
		int _accumulatedWheelDelta = 0;
		bool _isInWindow = false;
		bool _leftIsPressed = false;
		bool _rightIsPressed = false;
		std::queue<MouseEvent> _mouseEvents;
		
	};
}
