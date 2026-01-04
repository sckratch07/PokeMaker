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
}