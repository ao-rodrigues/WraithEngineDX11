#pragma once

namespace Wraith
{
	class Keyboard
	{
		friend class Window;
	public:
		class KeyEvent
		{
		public:
			enum class Type
			{
				Press,
				Release
			};

			KeyEvent(Type type, unsigned char keyCode) noexcept
				: _type(type)
				, _keyCode(keyCode)
			{}

			bool IsPress() const noexcept
			{
				return _type == Type::Press;
			}

			bool IsRelease() const noexcept
			{
				return _type == Type::Release;
			}

			unsigned char GetCode() const noexcept
			{
				return _keyCode;
			}

		private:
			Type _type;
			unsigned char _keyCode;
		};

		Keyboard() = default;
		Keyboard(const Keyboard&) = delete;
		Keyboard& operator=(const Keyboard&) = delete;

		/// <summary>
		/// Checks if a given key is currently being pressed.
		/// </summary>
		/// <param name="keyCode">The key code</param>
		/// <returns>True if it is, false if not</returns>
		bool KeyIsPressed(unsigned char keyCode) const noexcept;

		/// <summary>
		/// Returns the next key event from the event queue.
		/// </summary>
		/// <returns>Next key event</returns>
		std::optional<KeyEvent> GetKeyEvent() noexcept;

		/// <summary>
		/// Checks if there are any key events in the event queue.
		/// </summary>
		/// <returns>True if there are, false if not</returns>
		bool HasKeyEvents() const noexcept;

		/// <summary>
		/// Clears all key events from the event queue.
		/// </summary>
		void ClearKeyEvents() noexcept;

		/// <summary>
		/// Reads the next char from the char event queue.
		/// </summary>
		/// <returns>Next char</returns>
		std::optional<char> ReadChar() noexcept;

		/// <summary>
		/// Checks if there are any char events in the event queue.
		/// </summary>
		/// <returns>True if there are, false if not</returns>
		bool HasCharEvents() const noexcept;

		/// <summary>
		/// Clears the char event queue.
		/// </summary>
		void ClearCharEvents() noexcept;

		/// <summary>
		/// Clears all keyboard events.
		/// </summary>
		void ClearAllEvents() noexcept;

		void EnableAutoRepeat() noexcept;
		void DisableAutoRepeat() noexcept;
		bool AutoRepeatIsEnabled() const noexcept;

	private:
		void OnKeyPressed(unsigned char keyCode) noexcept;
		void OnKeyReleased(unsigned char keyCode) noexcept;
		void OnChar(char character) noexcept;
		void ClearKeyStates() noexcept;
		template<typename T>
		static void TrimEventQueue(std::queue<T>& eventQueue) noexcept;

		static constexpr unsigned int NUM_KEYS = 256u;
		static constexpr unsigned int EVENT_QUEUE_SIZE = 16u;

		bool _autoRepeatEnabled = false;
		std::bitset<NUM_KEYS> _keyStates;
		std::queue<KeyEvent> _keyEvents;
		std::queue<char> _charEvents;
	};
}
