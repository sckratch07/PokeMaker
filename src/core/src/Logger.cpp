#include "Core/Logger.hpp"


namespace Core
{
    std::shared_ptr<spdlog::logger> Logger::s_logger;

    void Logger::init(const std::string& name, const std::string& logFile)
    {
        if (s_logger)
            return;

        std::vector<spdlog::sink_ptr> sinks;
        sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());

        if (!logFile.empty())
        {
            sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFile, true));
        }
        
        s_logger = std::make_shared<spdlog::logger>(name, sinks.begin(), sinks.end());
        spdlog::register_logger(s_logger);

        s_logger->set_level(spdlog::level::trace);
        s_logger->set_pattern("[%Y-%m-%d %H:%M:%S] [%^%l%$] %v");
    }

    std::shared_ptr<spdlog::logger>& Logger::get()
    {
        return s_logger;
    }

    void Logger::shutdown()
    {
        if (s_logger)
        {
            s_logger.reset();
            spdlog::shutdown();
        }
    }
}