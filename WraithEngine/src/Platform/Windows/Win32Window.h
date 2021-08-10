#pragma once

#include "WraithException.h"
#include "Core/Window.h"

namespace Wraith
{
	class Win32Window : public Window
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
		
		Win32Window(const std::string& title, unsigned int width, unsigned int height);
		virtual ~Win32Window();

		unsigned int GetWidth() const override { return _width; }
		unsigned int GetHeight() const override { return _height; }
		std::optional<int> ProcessMessages() override;

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
		
		std::string _title;
		unsigned int _width;
		unsigned int _height;

		HWND _hWnd;
	};

	//Error exception helper macros
	#define WR_WINDOW_EXCEPTION(hr) Win32Window::Exception(__LINE__, __FILE__, hr)
	#define WR_WINDOW_LAST_EXCEPTION() Win32Window::Exception(__LINE__, __FILE__, GetLastError())
}

