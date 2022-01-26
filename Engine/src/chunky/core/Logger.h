#pragma once
#include <memory>
#include <string>

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Chunky
{
	class Logger
	{
	public:
		static void Initialise(const std::string& name);

		template<typename... Args>
		static void Trace(const std::string& message, Args&& ...args)
		{
			s_Logger->trace(message, std::forward<Args>(args)...);
		}

		template<typename... Args>
		static void Info(const std::string& message, Args&& ...args)
		{
			s_Logger->info(message, std::forward<Args>(args)...);
		}

		template<typename... Args>
		static void Warn(const std::string& message, Args&& ...args)
		{
			s_Logger->warn(message, std::forward<Args>(args)...);
		}

		template<typename... Args>
		static void Error(const std::string& message, Args&& ...args)
		{
			s_Logger->error(message, std::forward<Args>(args)...);
		}

		template<typename... Args>
		static void Critical(const std::string& message, Args&& ...args)
		{
			s_Logger->critical(message, std::forward<Args>(args)...);
		}

	private:
		static std::shared_ptr<spdlog::logger> s_Logger;

	};
}