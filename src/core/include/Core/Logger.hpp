#ifndef _CORE_LOGGER_HPP__
#define _CORE_LOGGER_HPP__

#include <spdlog/spdlog.h>
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
            const std::string& logFile = "PokeMaker.log");

        /**
         * @brief Récupère le logger principal.
         */
        inline static std::shared_ptr<spdlog::logger>& Get() { return s_logger; }
        
        private:
            static std::shared_ptr<spdlog::logger> s_logger;
    };
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