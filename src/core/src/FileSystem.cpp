#include "Core/FileSystem.hpp"
#include <filesystem>
#include <fstream>
#include <sstream>

namespace fs = std::filesystem;

namespace Core
{

bool FileSystem::exists(const std::string& path)
{
    return fs::exists(fs::u8path(path));
}

std::string FileSystem::readFileToString(const std::string& path)
{
    std::ifstream in(path, std::ios::in | std::ios::binary);
    if (!in) return {};

    std::ostringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

std::vector<std::string> FileSystem::listFiles(const std::string& directory)
{
    std::vector<std::string> out;
    try
    {
        for (auto &entry : fs::directory_iterator(fs::u8path(directory)))
        {
            if (entry.is_regular_file()) {
                out.push_back(entry.path().string());
            }
        }
    } catch (...)
    {
        // silence : on renvoie un vecteur vide si répertoire invalide
    }
    return out;
}

std::string FileSystem::join(const std::string& a, const std::string& b)
{
    fs::path pa = fs::u8path(a);
    fs::path pb = fs::u8path(b);
    fs::path res = pa / pb;
    return res.string();
}

} // namespace Core
