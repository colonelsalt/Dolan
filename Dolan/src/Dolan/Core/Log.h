#pragma once

#include "Base.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Dolan {
	class Log
	{
	public:
		static void Init();

		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define DN_CORE_TRACE(...) ::Dolan::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define DN_CORE_INFO(...)  ::Dolan::Log::GetCoreLogger()->info(__VA_ARGS__)
#define DN_CORE_WARN(...)  ::Dolan::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define DN_CORE_ERROR(...) ::Dolan::Log::GetCoreLogger()->error(__VA_ARGS__)
#define DN_CORE_CRITICAL(...) ::Dolan::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define DN_TRACE(...)      ::Dolan::Log::GetClientLogger()->trace(__VA_ARGS__)
#define DN_INFO(...)       ::Dolan::Log::GetClientLogger()->info(__VA_ARGS__)
#define DN_WARN(...)       ::Dolan::Log::GetClientLogger()->warn(__VA_ARGS__)
#define DN_ERROR(...)      ::Dolan::Log::GetClientLogger()->error(__VA_ARGS__)
#define DN_CRITICAL(...)      ::Dolan::Log::GetClientLogger()->critical(__VA_ARGS__)
