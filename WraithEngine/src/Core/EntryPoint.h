#pragma once

#ifdef WR_PLATFORM_WINDOWS

	extern Wraith::Application Wraith::CreateApplication();

	int main()
	{
		Wraith::Logger::Init();

		WR_CORE_LOG_INFO("Wraith initialized!");
		
		auto app = Wraith::CreateApplication();
		return app.Run();
	}

#endif