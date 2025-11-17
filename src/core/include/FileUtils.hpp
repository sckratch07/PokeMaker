#ifndef _CORE_FILE_UTILS_HPP__
#define _CORE_FILE_UTILS_HPP__

#include <string>

namespace Core
{
    bool FileExists(const std::string& path);
    std::string GetFileName(const std::string& path);
    std::string GetFileExtension(const std::string& path);

} // namespace Core

#endif
