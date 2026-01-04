#include "Core/Project.hpp"
#include "Core/Logger.hpp"
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

namespace Core
{
    bool Project::create(const std::string& name, const std::string& path)
    {
        m_name = name;
        m_path = path;
        return true;
    }

    bool Project::load(const std::string& path)
    {
        try
        {
            std::ifstream file(path + "/data/ProjectData.json");
            if (!file.is_open())
            {
                LOG_ERROR("[Project]: Failed to open project file for loading.");
                return false;
            }

            json j;
            file >> j;
            m_name = j.value("name", "");
            m_path = j.value("path", "");

            file.close();

            LOG_DEBUG("[Project]: Project loaded successfully.");
            return true;
        }
        catch(const std::exception& e)
        {
            LOG_ERROR("[Project]: Exception while loading project: \n {}", e.what());
            return false;
        }
    }

    bool Project::save() const
    {
        if ( m_name.empty() && m_path.empty()) return false;
        try
        {
            std::ofstream file(m_path + "/data/ProjectData.json");
            if (!file.is_open())
            {
                LOG_ERROR("[Project]: Failed to open project file for saving.");
                return false;
            }

            json j;
            j["name"] = m_name;
            j["path"] = m_path;
            file << j.dump(4);
            file.close();

            LOG_DEBUG("[Project]: Project saved successfully.");
            return true;
        }
        catch(const std::exception& e)
        {
            LOG_ERROR("[Project]: Exception while saving project: \n {}", e.what());
            return false;
        }
    }
}