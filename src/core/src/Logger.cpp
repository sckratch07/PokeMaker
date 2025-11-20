#include "Core/Logger.hpp"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>

namespace Core
{

namespace
{
    // Formate l'heure locale à partir du chrono::system_clock
    static std::string timeNow()
    {
        using namespace std::chrono;
        auto now = system_clock::now();
        auto now_t = system_clock::to_time_t(now);
        std::tm tm;
#if defined(_WIN32)
        localtime_s(&tm, &now_t);
#else
        localtime_r(&now_t, &tm);
#endif
        char buffer[64];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);

        // Millisecondes
        auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;
        char out[96];
        std::snprintf(out, sizeof(out), "%s.%03lld", buffer, static_cast<long long>(ms.count()));
        return std::string(out);
    }

    static const char* levelToString(Logger::Level l)
    {
        switch (l) {
            case Logger::Level::Trace:   return "TRACE";
            case Logger::Level::Debug:   return "DEBUG";
            case Logger::Level::Info:    return "INFO";
            case Logger::Level::Warning: return "WARN";
            case Logger::Level::Error:   return "ERROR";
            case Logger::Level::Fatal:   return "FATAL";
            default: return "UNKNOWN";
        }
    }
}

Logger& Logger::instance()
{
    static Logger s_instance;
    return s_instance;
}

Logger::Logger()
    : m_level(Level::Info)
{
}

Logger::~Logger()
{
    if (m_file.is_open()) m_file.close();
}

void Logger::setLevel(Level level)
{
    std::lock_guard lock(m_mutex);
    m_level = level;
}

bool Logger::setLogFile(const std::string& path)
{
    std::lock_guard lock(m_mutex);
    if (m_file.is_open()) m_file.close();
    m_file.open(path, std::ios::out | std::ios::app);
    m_fileEnabled = m_file.is_open();
    return m_fileEnabled;
}

void Logger::trace(const std::string& msg)   { log(Level::Trace, msg); }
void Logger::debug(const std::string& msg)   { log(Level::Debug, msg); }
void Logger::info(const std::string& msg)    { log(Level::Info, msg); }
void Logger::warning(const std::string& msg) { log(Level::Warning, msg); }
void Logger::error(const std::string& msg)   { log(Level::Error, msg); }
void Logger::fatal(const std::string& msg)   { log(Level::Fatal, msg); }

void Logger::log(Level lvl, const std::string& msg)
{
    std::lock_guard lock(m_mutex);
    if (lvl < m_level) return;

    std::ostringstream ss;
    ss << "[" << timeNow() << "] ";
    ss << "[" << levelToString(lvl) << "] ";
    ss << msg << "\n";

    // Console
    std::cout << ss.str();
    std::cout.flush();

        // Fichier
        if (m_fileEnabled && m_file.is_open()) {
            m_file << ss.str();
            m_file.flush();
        }
    }
} // namespace Core
