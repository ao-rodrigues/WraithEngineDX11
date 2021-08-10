#include "wrpch.h"
#include "Logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Wraith
{
	std::shared_ptr<spdlog::logger> Logger::s_coreLogger;
	std::shared_ptr<spdlog::logger> Logger::s_clientLogger;

	void Logger::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_coreLogger = spdlog::stdout_color_mt("Wraith");
		s_coreLogger->set_level(spdlog::level::trace);

		s_clientLogger = spdlog::stdout_color_mt("App");
		s_clientLogger->set_level(spdlog::level::trace);
	}
}