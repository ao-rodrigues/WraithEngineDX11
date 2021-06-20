#include "Window.h"

#include <sstream>

using namespace Wraith;

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	try
	{
		Window window(800, 600, "Test Window");
		int wheel = 0;

		// Message pump
		MSG msg;
		BOOL result;
		while ((result = GetMessage(&msg, nullptr, 0, 0)) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			while(window.mouse.HasMouseEvents())
			{
				const auto e = window.mouse.GetMouseEvent();

				switch (e->GetType())
				{
				case Mouse::MouseEvent::Type::Leave:
					window.SetTitle("Gone!");
					break;

				case Mouse::MouseEvent::Type::Move:
					{
						std::ostringstream oss;
						oss << "Mouse moved to (" << e->GetPosX() << "," << e->GetPosY() << ")";
						window.SetTitle(oss.str());
					}
					break;
				case Mouse::MouseEvent::Type::WheelUp:
					{
						wheel++;
						std::ostringstream oss;
						oss << "Wheel: " << wheel;
						window.SetTitle(oss.str());
					}
					break;
				case Mouse::MouseEvent::Type::WheelDown:
					{
						wheel--;
						std::ostringstream oss;
						oss << "Wheel: " << wheel;
						window.SetTitle(oss.str());
					}
				break;
				}
				
			}
		}

		if(result == -1)
		{
			return -1;
		}
		
		return msg.wParam;
	}
	catch (const WraithException& e)
	{
		MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e)
	{
		MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, "No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}

	return -1;
}
