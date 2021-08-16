#include "wrpch.h"

#include "Events/EventBus.h"
#include "Events/MouseEvents.h"
#include "Events/KeyboardEvents.h"
#include "Core/Input.h"

#include "Win32Window.h"

namespace Wraith
{
	#pragma region Win32Window
	
	Win32Window::Win32Window(const std::string& title, unsigned int width, unsigned int height)
		: _title(title)
		, _width(width)
		, _height(height)
	{
		// Calculate window size based on desired client region size
		RECT windowRect;
		windowRect.left = 100;
		windowRect.right = _width + windowRect.left;
		windowRect.top = 100;
		windowRect.bottom = _height + windowRect.top;

		if(AdjustWindowRect(&windowRect, WS_CAPTION | WS_MINIMIZEBOX |WS_SYSMENU, FALSE) == 0)
		{
			throw WRAITH_WINDOW_LAST_EXCEPTION();
		}
		
		// Create window and get hWnd
		_hWnd = CreateWindow(
			WindowClass::GetName(),
			title.c_str(),
			WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			windowRect.right - windowRect.left,
			windowRect.bottom - windowRect.top,
			nullptr,
			nullptr,
			WindowClass::GetInstance(),
			this
		);

		if(_hWnd == nullptr)
		{
			throw WRAITH_WINDOW_LAST_EXCEPTION();
		}

		// Show window
		ShowWindow(_hWnd, SW_SHOWDEFAULT);
	}

	Win32Window::~Win32Window()
	{
		DestroyWindow(_hWnd);
	}

	std::optional<int> Win32Window::ProcessMessages()
	{
		MSG msg;
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{
				return msg.wParam;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return {};
	}

	LRESULT WINAPI Win32Window::HandleMessageSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
	{
		if (msg == WM_NCCREATE)
		{
			// Extract pointer to Window class from creation data
			const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
			auto* const pWindow = static_cast<Win32Window*>(pCreate->lpCreateParams);

			// Set WinAPI-managed user data to store a pointer to our Window class
			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));

			// Set message proc to normal (non-setup) handler now that setup is finished
			SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Win32Window::HandleMessageThunk));

			// Forward message to our handler
			return pWindow->HandleMessage(hWnd, msg, wParam, lParam);
		}

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	LRESULT WINAPI Win32Window::HandleMessageThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
	{
		// Retrieve pointer to Window class
		auto* const pWindow = reinterpret_cast<Win32Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

		// Forward message to Window class handler
		return pWindow->HandleMessage(hWnd, msg, wParam, lParam);
	}

	LRESULT Win32Window::HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
	{	
		switch (msg)
		{
		case WM_CLOSE:
			PostQuitMessage(0);
			return 0;
		case WM_KILLFOCUS:
			Input::ClearKeyStates();
			break;

		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		{
			if(!(lParam & 0x40000000))
			{
				EventBus::Send<KeyPressedEvent>(static_cast<unsigned char>(wParam));
			}
			break;
		}
		case WM_KEYUP:
		case WM_SYSKEYUP:
		{
			EventBus::Send<KeyReleasedEvent>(static_cast<unsigned char>(wParam));
			break;
		}
		case WM_CHAR:
		{
			EventBus::Send<KeyTypedEvent>(static_cast<char>(wParam));
			break;
		}
			
		case WM_MOUSEMOVE:
		{
			const auto [x, y] = MAKEPOINTS(lParam);

			// If in client region, log move, enter, and capture mouse
			if(x >= 0 && x < _width && y >= 0 && y < _height)
			{
				EventBus::Send<MouseMovedEvent>(x, y);
				
				if(!Input::IsMouseInWindow())
				{
					SetCapture(_hWnd);
					EventBus::Send<MouseEnterEvent>();
				}
				
			}
			// If not in client region, log move if either left or right is pressed
			else
			{
				if(Input::IsMouseButtonDown(MouseButton::Left) || Input::IsMouseButtonDown(MouseButton::Right))
				{
					EventBus::Send<MouseMovedEvent>(x, y);
				}
				
				// Button up, release capture and log mouse leave event
				else
				{
					ReleaseCapture();
					EventBus::Send<MouseLeaveEvent>();
				}
				
			}
			break;
		}
		case WM_LBUTTONDOWN:
		{
			EventBus::Send<MouseButtonPressedEvent>(MouseButton::Left);
			break;
		}
		case WM_LBUTTONUP:
		{
			const auto [x, y] = MAKEPOINTS(lParam);
			EventBus::Send<MouseButtonReleasedEvent>(MouseButton::Left);

			if(x < 0 || x >= _width || y < 0 || y >= _height)
			{
				ReleaseCapture();
				EventBus::Send<MouseLeaveEvent>();
			}
			
			break;
		}
		case WM_RBUTTONDOWN:
		{
			EventBus::Send<MouseButtonPressedEvent>(MouseButton::Right);
			break;
		}
		case WM_RBUTTONUP:
		{
			const auto [x, y] = MAKEPOINTS(lParam);
			EventBus::Send<MouseButtonReleasedEvent>(MouseButton::Right);

			if(x < 0 || x >= _width || y < 0 || y >= _height)
			{
				ReleaseCapture();
				EventBus::Send<MouseLeaveEvent>();
			}
			break;
		}
		case WM_MBUTTONDOWN:
		{
			EventBus::Send<MouseButtonPressedEvent>(MouseButton::Middle);
			break;
		}
		case WM_MBUTTONUP:
		{
			const auto [x, y] = MAKEPOINTS(lParam);
			EventBus::Send<MouseButtonReleasedEvent>(MouseButton::Middle);

			if(x < 0 || x >= _width || y < 0 || y >= _height)
			{
				ReleaseCapture();
				EventBus::Send<MouseLeaveEvent>();
			}
			break;
		}
		case WM_MOUSEWHEEL:
		{
			int delta = GET_WHEEL_DELTA_WPARAM(wParam);
			if (delta != 0)
			{
				// Flatten the input to an OS-independent range (-1, 1)
				delta = (delta < 0) ? -1 : 1;
				EventBus::Send<MouseWheelDeltaEvent>(delta);
			}
		}
			
		}

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	#pragma endregion 

	#pragma region WindowClass

	Win32Window::WindowClass Win32Window::WindowClass::s_wndClass;

	Win32Window::WindowClass::WindowClass() noexcept
		: _hInstance(GetModuleHandle(nullptr))
	{
		// Register window class
		WNDCLASSEX wc = {0};
		wc.cbSize = sizeof(wc);
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = HandleMessageSetup;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = GetInstance();
		wc.hIcon = nullptr;
		wc.hCursor = nullptr;
		wc.hbrBackground = nullptr;
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = GetName();
		wc.hIconSm = nullptr;
		
		RegisterClassEx(&wc);
	}

	Win32Window::WindowClass::~WindowClass()
	{
		UnregisterClass(WND_CLASS_NAME, GetInstance());
	}

	const char* Win32Window::WindowClass::GetName() noexcept
	{
		return WND_CLASS_NAME;
	}

	HINSTANCE Win32Window::WindowClass::GetInstance() noexcept
	{
		return s_wndClass._hInstance;
	}
	
	#pragma endregion 
}
