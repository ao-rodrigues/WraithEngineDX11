#include "Window.h"

using namespace Wraith;

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	Window window(800, 600, "Test Window");

	// Message pump
	MSG msg;
	BOOL result;
	while ((result = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if(result == -1)
	{
		return -1;
	}
	
	return msg.wParam;
}
