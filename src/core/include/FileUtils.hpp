#ifndef _CORE_FILE_UTILS_HPP__
#define _CORE_FILE_UTILS_HPP__

#include <string>

namespace Core
{
    bool fileExists(const std::string& path);
    std::string getFileName(const std::string& path);
    std::string getFileExtension(const std::string& path);

} // namespace Core

#endif
