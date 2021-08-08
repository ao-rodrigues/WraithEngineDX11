#pragma once

#ifdef WR_PLATFORM_WINDOWS

	extern Wraith::Application Wraith::CreateApplication();

	int main()
	{
		auto app = Wraith::CreateApplication();
		return app.Run();
	}

#endif