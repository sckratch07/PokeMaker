#ifndef _CORE_LOGGER_HPP__
#define _CORE_LOGGER_HPP__

#include <string>
#include <mutex>
#include <fstream>
#include <memory>

namespace Core
{
/**
 * @brief Logger thread-safe simple avec niveaux.
 *
 * Utilisation:
 * @code
 * Core::Logger::instance().setLogFile("logs/app.log");
 * Core::Logger::instance().info("Démarrage...");
 * @endcode
 */
class Logger
{
public:
    enum class Level
    {
        Trace = 0,
        Debug,
        Info,
        Warning,
        Error,
        Fatal
    };

    static Logger& instance();

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    /**
     * @brief Définit le niveau minimal de journalisation (par défaut Info).
     */
    void setLevel(Level level);

    /**
     * @brief Définit un fichier de log (optionnel). Si vide -> only console.
     * @param path Chemin du fichier de log.
     * @return true si ouverture ok, false sinon.
     */
    bool setLogFile(const std::string& path);

    // Méthodes de log concises
    void trace(const std::string& msg);
    void debug(const std::string& msg);
    void info(const std::string& msg);
    void warning(const std::string& msg);
    void error(const std::string& msg);
    void fatal(const std::string& msg);

private:
    Logger();
    ~Logger();

    void log(Level lvl, const std::string& msg);

    Level m_level;
    std::mutex m_mutex;
    std::ofstream m_file;
    bool m_fileEnabled = false;
};

} // namespace Core

#endif
