#include "Core/Logger.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Core
{
    std::shared_ptr<spdlog::logger> Logger::s_logger = nullptr;

    void Logger::Init(const std::string& name, const std::string& logFile)
    {
        if (s_logger)
            return;

        std::vector<spdlog::sink_ptr> sinks;

        auto consoleSink =
            std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        consoleSink->set_pattern("[%H:%M:%S] [%^%l%$] %v");
        sinks.push_back(consoleSink);

        auto fileSink =
            std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFile, true);
        fileSink->set_pattern("[%Y-%m-%d %H:%M:%S] [%l] %v");
        sinks.push_back(fileSink);

        s_logger = std::make_shared<spdlog::logger>(
            name, sinks.begin(), sinks.end());

        spdlog::register_logger(s_logger);

        s_logger->set_level(spdlog::level::trace);
        s_logger->flush_on(spdlog::level::warn);
    }

    std::shared_ptr<spdlog::logger>& Logger::Get()
    {
        return s_logger;
    }
}