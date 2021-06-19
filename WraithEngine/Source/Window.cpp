#include "Window.h"

#include <sstream>

using namespace Wraith;

#pragma region Window
Window::Window(const int width, const int height, const char* name)
	: _width(width)
	, _height(height)
{
	// Calculate window size based on desired client region size
	RECT windowRect;
	windowRect.left = 100;
	windowRect.right = _width + windowRect.left;
	windowRect.top = 100;
	windowRect.bottom = _width + windowRect.top;

	if(AdjustWindowRect(&windowRect, WS_CAPTION | WS_MINIMIZEBOX |WS_SYSMENU, FALSE) == 0)
	{
		throw WR_WINDOW_LAST_EXCEPTION();
	}
	
	// Create window and get hWnd
	_hWnd = CreateWindow(
		WindowClass::GetName(),
		name,
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
		throw WR_WINDOW_LAST_EXCEPTION();
	}

	// Show window
	ShowWindow(_hWnd, SW_SHOWDEFAULT);
}

Window::~Window()
{
	DestroyWindow(_hWnd);
}

LRESULT WINAPI Window::HandleMessageSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	if (msg == WM_NCCREATE)
	{
		// Extract pointer to Window class from creation data
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		auto* const pWindow = static_cast<Window*>(pCreate->lpCreateParams);

		// Set WinAPI-managed user data to store a pointer to our Window class
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));

		// Set message proc to normal (non-setup) handler now that setup is finished
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMessageThunk));

		// Forward message to our handler
		return pWindow->HandleMessage(hWnd, msg, wParam, lParam);
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT WINAPI Window::HandleMessageThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	// Retrieve pointer to Window class
	auto* const pWindow = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

	// Forward message to Window class handler
	return pWindow->HandleMessage(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

#pragma endregion 

#pragma region Window::Exception

Window::Exception::Exception(int line, const char* file, HRESULT hr) noexcept
	: WraithException(line, file)
	, _hr(hr)
{ }

const char* Window::Exception::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "[Error Code] " << GetErrorCode() << std::endl
		<< "[Description] " << GetErrorString() << std::endl
		<< GetOriginString();

	_whatBuffer = oss.str();
	return _whatBuffer.c_str();
}

const char* Window::Exception::GetType() const noexcept
{
	return "Wraith Window Exception";
}

std::string Window::Exception::TranslateErrorCode(HRESULT hr) noexcept
{
	char* pMsgBuffer = nullptr;
	DWORD msgLength = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr,
		hr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPSTR>(&pMsgBuffer),
		0,
		nullptr
	);

	if(msgLength == 0)
	{
		return "Unidentified error code";
	}

	std::string errorString = pMsgBuffer;
	LocalFree(pMsgBuffer);
	return errorString;
}

HRESULT Window::Exception::GetErrorCode() const noexcept
{
	return _hr;
}

std::string Window::Exception::GetErrorString() const noexcept
{
	return TranslateErrorCode(_hr);
}


#pragma endregion 

#pragma region WindowClass

Window::WindowClass Window::WindowClass::s_wndClass;

Window::WindowClass::WindowClass() noexcept
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

Window::WindowClass::~WindowClass()
{
	UnregisterClass(WND_CLASS_NAME, GetInstance());
}

const char* Window::WindowClass::GetName() noexcept
{
	return WND_CLASS_NAME;
}

HINSTANCE Window::WindowClass::GetInstance() noexcept
{
	return s_wndClass._hInstance;
}


#pragma endregion 
