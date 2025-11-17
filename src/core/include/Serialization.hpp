#ifndef _CORE_SERIALIZATION_HPP__
#define _CORE_SERIALIZATION_HPP__

#include <nlohmann/json.hpp>
#include <string>
#include <fstream>

using json = nlohmann::json;

namespace Core
{
    inline bool saveJsonToFile(const json& j, const std::string& path)
    {
        std::ofstream ofs(path);
        if (!ofs.is_open()) return false;
        ofs << j.dump(4);
        return true;
    }

    inline bool loadJsonFromFile(json& j, const std::string& path)
    {
        std::ifstream ifs(path);
        if (!ifs.is_open()) return false;
        ifs >> j;
        return true;
    }
} // namespace Core

#endif
