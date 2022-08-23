#pragma once

#include <memory>

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#pragma warning(pop)

namespace Sakura
{
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

#define SAKURA_CORE_TRACE(...) ::Sakura::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SAKURA_CORE_INFO(...)  ::Sakura::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SAKURA_CORE_WARN(...)  ::Sakura::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SAKURA_CORE_ERROR(...) ::Sakura::Log::GetCoreLogger()->error(__VA_ARGS__)

#define SAKURA_TRACE(...) ::Sakura::Log::GetClientLogger()->trace(__VA_ARGS__)
#define SAKURA_INFO(...)  ::Sakura::Log::GetClientLogger()->info(__VA_ARGS__)
#define SAKURA_WARN(...)  ::Sakura::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SAKURA_ERROR(...) ::Sakura::Log::GetClientLogger()->error(__VA_ARGS__)