#pragma once

#include "WraithWin.h"

#include "WraithException.h"
#include "Keyboard.h"
#include "Mouse.h"

namespace Wraith
{
	class Window
	{
	public:
		class Exception : public WraithException
		{
		public:
			Exception(int line, const char* file, HRESULT hr) noexcept;

			const char* what() const noexcept override;
			const char* GetType() const noexcept override;
			static std::string TranslateErrorCode(HRESULT hr) noexcept;
			HRESULT GetErrorCode() const noexcept;
			std::string GetErrorString() const noexcept;

		private:
			HRESULT _hr;
		};
		
		Window(int width, int height, const char* name);
		~Window();
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		void SetTitle(const std::string& title) noexcept;

		Keyboard keyboard;
		Mouse mouse;

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

// Error exception helper macros
#define WR_WINDOW_EXCEPTION(hr) Window::Exception(__LINE__, __FILE__, hr)
#define WR_WINDOW_LAST_EXCEPTION() Window::Exception(__LINE__, __FILE__, GetLastError())
	
}
