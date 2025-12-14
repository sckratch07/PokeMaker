#ifndef _CORE_LOGGER_HPP__
#include <string>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Core
{
    /**
    * @brief Système de logging centralisé du moteur.
    *
    * Wrapper autour de spdlog permettant :
    * - une configuration unique (format, niveau)
    * - une utilisation simple dans tout le moteur
    * - une séparation claire Editor / Runtime
    *
    * Le Logger doit être initialisé au démarrage de l'application
    * et accessible globalement.
    */
    class Logger
    {
    public:
        /**
        * @brief Initialise le système de logging
        *
        * @param name Nom du logger
        * @param logFile Chemin du fichier de log (optionnel)
        */
        static void init(const std::string& name = "PokeMaker",
            const std::string& logFile = "");

        /**
        * @brief Récupère le logger principal
        */
        static std::shared_ptr<spdlog::logger>& get();

        /**
        * @brief Supprime le logger
        */
        static void shutdown();

    private:
        static std::shared_ptr<spdlog::logger> s_logger;
    };
}

// Macros utilitaires
#define PM_LOG_TRACE(...) ::Core::Logger::get()->trace(__VA_ARGS__)
#define PM_LOG_INFO(...) ::Core::Logger::get()->info(__VA_ARGS__)
#define PM_LOG_WARN(...) ::Core::Logger::get()->warn(__VA_ARGS__)
#define PM_LOG_ERROR(...) ::Core::Logger::get()->error(__VA_ARGS__)
#define PM_LOG_CRITICAL(...) ::Core::Logger::get()->critical(__VA_ARGS__)

#endif // _CORE_LOGGER_HPP__