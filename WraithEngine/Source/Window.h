#pragma once
#include "WraithWin.h"

namespace Wraith
{
	class Window
	{
	public:
		Window(int width, int height, const char* name) noexcept;
		~Window();
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

	private:
		class WindowClass
		{
		public:
			static const char* GetName() noexcept;
			static HINSTANCE GetInstance() noexcept;
		private:
			WindowClass() noexcept;
			~WindowClass();
			WindowClass(const WindowClass&) = delete;
			WindowClass& operator=(const WindowClass&) = delete;
			static constexpr const char* WND_CLASS_NAME = "Wraith Engine Window";
			static WindowClass s_wndClass;
			HINSTANCE _hInstance;
		};

		static LRESULT CALLBACK HandleMessageSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
		static LRESULT CALLBACK HandleMessageThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
		LRESULT HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
		
		int _width;
		int _height;
		HWND _hWnd;
	};

}
