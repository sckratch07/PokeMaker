#include "Core/Project.hpp"
#include "Core/Logger.hpp"
#include <nlohmann/json.hpp>
#include <filesystem>
#include <fstream>

using json = nlohmann::json;

namespace Core
{
    bool Project::create(const std::string& name, const std::string& path)
    {
        try
        {
            std::filesystem::create_directories(path + "/data");
            std::filesystem::create_directories(path + "/module/components");
            std::filesystem::create_directories(path + "/module/systems");
            std::filesystem::create_directories(path + "/resources");

            std::ofstream jsonFile(path + "/ProjectData.json");
            if (!jsonFile.is_open())
            {
                LOG_ERROR("[Project]: Failed to create ProjectData.json");
                return false;
            }

            json j;
            j["name"] = name;
            j["path"] = path;
            jsonFile << j;
            jsonFile.close();

            std::ofstream cmake(path + "/CMakeLists.txt");
            if (!cmake.is_open())
            {
                LOG_ERROR("[Project]: Failed to create CMakeLists.txt.");
                return false;
            }

            cmake << "cmake_minimum_required(VERSION 3.5)" << std::endl;
            cmake << "project(ProjectFile_" << name <<")\n" << std::endl;
            cmake << "add_library(${PROJECT_NAME} INTERFACE)" << std::endl;
            cmake << "target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/module/components ${CMAKE_CURRENT_SOURCE_DIR}/module/systems)" << std::endl;
            cmake.close();

            m_name = name;
            m_path = path;
            return true;
        }
        catch (const std::exception& e)
        {
            LOG_ERROR("[Project]: Exception while create project: \n {}", e.what());
            return false;
        }
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