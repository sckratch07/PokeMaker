#ifndef _CORE_LOGGER_HPP__
#define _CORE_LOGGER_HPP__

#include <iostream>
#include <string>

namespace Core
{
    enum class LogLevel { Info, Warning, Error };

    inline void Log(const std::string& msg, LogLevel level = LogLevel::Info)
    {
        switch(level)
        {
        case LogLevel::Info:    std::cout << "[INFO] "; break;
        case LogLevel::Warning: std::cout << "[WARN] "; break;
        case LogLevel::Error:   std::cerr << "[ERROR] "; break;
        }
    std::cout << msg << std::endl;
    }
} // namespace Core

#endif
