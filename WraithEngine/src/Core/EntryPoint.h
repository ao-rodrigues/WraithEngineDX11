#pragma once

#include "Core/Application.h"

#ifdef WR_PLATFORM_WINDOWS

extern Wraith::Application* Wraith::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Wraith::CreateApplication();
	app->Run();
	delete app;
}

#endif