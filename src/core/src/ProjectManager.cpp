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

    void ProjectManager::deleteMap(Map* map, std::shared_ptr<EntityManager>& manager)
    {
        auto it = std::find_if(m_maps.begin(), m_maps.end(),
            [&](const Map& m)
            {
                return &m == map;
            }
        );

        size_t index = std::distance(m_maps.begin(), it);
        if (!m_maps.empty() && index < m_maps.size())
        {
            for (unsigned int i = 0; i < map->m_entities.size(); i++)
                map->deleteEntity(i, manager);
            
            for (unsigned int i = 0; i < map->m_layers.size(); i++)
                map->deleteLayer(i, manager);

            for (size_t i = index; i < m_maps.size() - 1; i++)
            {
                std::swap(m_maps[i], m_maps[i + 1]);
            }
            m_maps.pop_back();
        }
    }
}