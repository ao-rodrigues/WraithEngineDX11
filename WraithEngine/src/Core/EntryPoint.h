#pragma once

#ifdef WR_PLATFORM_WINDOWS
#include "WraithException.h"

extern Wraith::Application Wraith::CreateApplication();

int main()
{
	try
	{
		Wraith::Logger::Init();

		WR_CORE_LOG_INFO("Wraith initialized!");
		
		auto app = Wraith::CreateApplication();
		return app.Run();
	}
	catch (const Wraith::WraithException& e)
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

#endif