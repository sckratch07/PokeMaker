#include "FileUtils.hpp"
#include <filesystem>

namespace Core
{
    bool FileExists(const std::string& path)
    {
        return std::filesystem::exists(path);
    }

    std::string GetFileName(const std::string& path)
    {
        return std::filesystem::path(path).filename().string();
    }

    std::string GetFileExtension(const std::string& path)
    {
        return std::filesystem::path(path).extension().string();
    }
} // namespace Core
