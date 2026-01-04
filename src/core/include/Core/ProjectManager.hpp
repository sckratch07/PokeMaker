#ifndef _CORE_PROJECT_MANAGER_HPP__
#define _CORE_PROJECT_MANAGER_HPP__

#include "Core/Project.hpp"
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

        std::unique_ptr<Project>& getProject() { return m_currentProject; }

    private:
        std::unique_ptr<Project> m_currentProject = nullptr;
    };
}

#endif