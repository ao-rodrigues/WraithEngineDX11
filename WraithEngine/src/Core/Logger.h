#pragma once

#include <spdlog/spdlog.h>

namespace Wraith
{
	class Logger
	{
	public:
		static void Init();

		static const std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_coreLogger; }
		static const std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_clientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_coreLogger;
		static std::shared_ptr<spdlog::logger> s_clientLogger;
	};
}

#ifdef WRAITH_DEBUG
// Core logging macros
#define WRAITH_CORE_LOG_TRACE(...)   ::Wraith::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define WRAITH_CORE_LOG_INFO(...)    ::Wraith::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define WRAITH_CORE_LOG_WARN(...)    ::Wraith::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define WRAITH_CORE_LOG_ERROR(...)   ::Wraith::Logger::GetCoreLogger()->error(__VA_ARGS__)

// Client logging macros
#define WRAITH_LOG_TRACE(...)        ::Wraith::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define WRAITH_LOG_INFO(...)         ::Wraith::Logger::GetClientLogger()->info(__VA_ARGS__)
#define WRAITH_LOG_WARN(...)         ::Wraith::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define WRAITH_LOG_ERROR(...)        ::Wraith::Logger::GetClientLogger()->error(__VA_ARGS__)

#else
#ifdef WRAITH_RELEASE

// Core logging macros
#define WRAITH_CORE_LOG_TRACE(...)   
#define WRAITH_CORE_LOG_INFO(...)    
#define WRAITH_CORE_LOG_WARN(...)    
#define WRAITH_CORE_LOG_ERROR(...)   
#define WRAITH_CORE_LOG_FATAL(...)   

// Client logging macros
#define WRAITH_LOG_TRACE(...)
#define WRAITH_LOG_INFO(...) 
#define WRAITH_LOG_WARN(...) 
#define WRAITH_LOG_ERROR(...)
#define WRAITH_LOG_FATAL(...)

#endif
#endif
