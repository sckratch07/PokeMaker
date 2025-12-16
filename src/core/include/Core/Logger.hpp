#ifndef _CORE_LOGGER_HPP__
#define _CORE_LOGGER_HPP__

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <memory>
#include <string>

namespace Core
{
    class Logger
    {
    public:
        /**
         * @brief Initialise le système de log.
         * @param name Nom du logger.
         * @param logFile Chemin du fichier de log.
         */
        static void Init(
            const std::string& name = "PokeMaker",
            const std::string& logFile = "PokeMaker.log")
        {
            if (s_logger)
                return;

            std::vector<spdlog::sink_ptr> sinks;

            // Console (colorée)
            auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            consoleSink->set_pattern("[%H:%M:%S] [%^%l%$] %v");
            sinks.push_back(consoleSink);

            // Fichier
            auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFile, true);
            fileSink->set_pattern("[%Y-%m-%d %H:%M:%S] [%l] %v");
            sinks.push_back(fileSink);

            s_logger = std::make_shared<spdlog::logger>(name, sinks.begin(), sinks.end());
            spdlog::register_logger(s_logger);

            s_logger->set_level(spdlog::level::trace);
            s_logger->flush_on(spdlog::level::warn);
        }

        /**
         * @brief Récupère le logger principal.
         */
        inline static std::shared_ptr<spdlog::logger>& Get()
        {
            return s_logger;
        }
        
        private:
            static std::shared_ptr<spdlog::logger> s_logger;
    };

    std::shared_ptr<spdlog::logger> Logger::s_logger = nullptr;
}

// ================================
// Macros de logging
// ================================

#define LOG_TRACE(...)    ::Core::Logger::Get()->trace(__VA_ARGS__)
#define LOG_DEBUG(...)    ::Core::Logger::Get()->debug(__VA_ARGS__)
#define LOG_INFO(...)     ::Core::Logger::Get()->info(__VA_ARGS__)
#define LOG_WARN(...)     ::Core::Logger::Get()->warn(__VA_ARGS__)
#define LOG_ERROR(...)    ::Core::Logger::Get()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) ::Core::Logger::Get()->critical(__VA_ARGS__)

#endif