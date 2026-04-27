#pragma once

#include "krxpch.h"

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace Krux {
	class Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& Core()   { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& Client() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

#define KRX_CORE_TRACE(...)    ::Krux::Log::Core()->trace(__VA_ARGS__);
#define KRX_CORE_DEBUG(...)    ::Krux::Log::Core()->debug(__VA_ARGS__);
#define KRX_CORE_INFO(...)     ::Krux::Log::Core()->info(__VA_ARGS__);
#define KRX_CORE_WARN(...)     ::Krux::Log::Core()->warn(__VA_ARGS__);
#define KRX_CORE_ERROR(...)    ::Krux::Log::Core()->error(__VA_ARGS__);
#define KRX_CORE_CRITICAL(...) ::Krux::Log::Core()->critical(__VA_ARGS__);

#define KRX_TRACE(...)		   ::Krux::Log::Client()->trace(__VA_ARGS__);
#define KRX_DEBUG_LOG(...)	   ::Krux::Log::Client()->debug(__VA_ARGS__);
#define KRX_INFO(...)		   ::Krux::Log::Client()->info(__VA_ARGS__);
#define KRX_WARN(...)		   ::Krux::Log::Client()->warn(__VA_ARGS__);
#define KRX_ERROR(...)		   ::Krux::Log::Client()->error(__VA_ARGS__);
#define KRX_CRITICAL(...)	   ::Krux::Log::Client()->critical(__VA_ARGS__);
