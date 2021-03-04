#pragma once

#include <memory>

#include <PencilEngine/core.h>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace pencil
{
	class PENCIL_API Log
	{
	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger> &getCoreLogger()
		{
			return s_coreLogger;
		}

		inline static std::shared_ptr<spdlog::logger> &getClientLogger()
		{
			return s_clientLogger;
		}

	private:
		static std::shared_ptr<spdlog::logger> s_coreLogger;
		static std::shared_ptr<spdlog::logger> s_clientLogger;
	};
}

#define PC_CORE_TRACE(...)    ::pencil::Log::getCoreLogger()->trace(__VA_ARGS__)
#define PC_CORE_INFO(...)     ::pencil::Log::getCoreLogger()->info(__VA_ARGS__)
#define PC_CORE_WARN(...)     ::pencil::Log::getCoreLogger()->warn(__VA_ARGS__)
#define PC_CORE_ERROR(...)    ::pencil::Log::getCoreLogger()->error(__VA_ARGS__)
#define PC_CORE_FATAL(...)    ::pencil::Log::getCoreLogger()->fatal(__VA_ARGS__)

#define PC_TRACE(...)    ::pencil::Log::getClientLogger()->trace(__VA_ARGS__)
#define PC_INFO(...)     ::pencil::Log::getClientLogger()->info(__VA_ARGS__)
#define PC_WARN(...)     ::pencil::Log::getClientLogger()->warn(__VA_ARGS__)
#define PC_ERROR(...)    ::pencil::Log::getClientLogger()->error(__VA_ARGS__)
#define PC_FATAL(...)    ::pencil::Log::getClientLogger()->fatal(__VA_ARGS__)
