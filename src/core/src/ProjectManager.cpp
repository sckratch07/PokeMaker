#include "Core/ProjectManager.hpp"

namespace Core
{
    void ProjectManager::createNewProject(const std::string& name, const std::string& path)
    {
        if (m_currentProject == nullptr)
            m_currentProject = std::make_unique<Project>(name, path);
        else if (m_currentProject->isValid())
            m_currentProject = nullptr;

        m_currentProject->create(name, path);
    }

    void ProjectManager::loadProject(const std::string& path)
    {
        if (m_currentProject == nullptr)
            m_currentProject = std::make_unique<Project>();
        else if (m_currentProject->isValid())
            m_currentProject = nullptr;

        m_currentProject->load(path);
    }

    void ProjectManager::saveProject() const
    {
        if (m_currentProject && m_currentProject->isValid())
            m_currentProject->save();
    }

    void ProjectManager::closeProject()
    {
        m_currentProject = nullptr;
    }

    Map* ProjectManager::createNewMap(const std::string& name, int mapSize[2], int tileSize[2])
    {
        Map newMap(name, mapSize[0], mapSize[1], tileSize[0], tileSize[1]);
        m_maps.push_back(newMap);
        return &m_maps.back();
    }

    void ProjectManager::deleteMap(Map* map)
    {
        auto it = std::find_if(m_maps.begin(), m_maps.end(),
            [&](const Map& m)
            {
                return &m == map;
            }
        );
        std::swap(m_maps[std::distance(m_maps.begin(), it)], m_maps.back());
        m_maps.pop_back();
    }
}