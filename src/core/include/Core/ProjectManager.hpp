#ifndef _CORE_PROJECT_MANAGER_HPP__
#define _CORE_PROJECT_MANAGER_HPP__

#include "Core/Project.hpp"
#include "Core/Map/Map.hpp"
#include <memory>

namespace Core
{
    class ProjectManager
    {
    public:
        ProjectManager() = default;
        ~ProjectManager() = default;

        void createNewProject(const std::string& name, const std::string& path);
        void loadProject(const std::string& path);
        void saveProject() const;
        void closeProject();

        Map* createNewMap(const std::string& name, int mapSize[2], int tileSize[2]);
        void deleteMap(Map* map, std::shared_ptr<EntityManager>& manager);

        std::unique_ptr<Project>& getProject() { return m_currentProject; }
        std::vector<Map>& getMaps() { return m_maps; }

    private:
        std::unique_ptr<Project> m_currentProject = nullptr;
        std::vector<Map> m_maps;
    };
}

#endif