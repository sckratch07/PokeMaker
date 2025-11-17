#include <FileUtils.hpp>
#include <filesystem>

namespace Core
{
    bool fileExists(const std::string& path)
    {
        return std::filesystem::exists(path);
    }

    std::string getFileName(const std::string& path)
    {
        return std::filesystem::path(path).filename().string();
    }

    std::string getFileExtension(const std::string& path)
    {
        return std::filesystem::path(path).extension().string();
    }
} // namespace Core
