#include "Editor/Project/ProjectManager.hpp"
#include <iostream>

namespace Editor::Project {

ProjectManager::ProjectManager()
{
    CreateEmptyProject();
}

ProjectManager::~ProjectManager()
{
}

void ProjectManager::Update(float dt)
{
    if (m_project)
        m_project->Update(dt);
}

void ProjectManager::CreateEmptyProject()
{
    m_project = new Project;
    m_projectPath.clear();
}

bool ProjectManager::LoadProject(const std::string& path)
{
    Project loaded;
    if (!m_serializer.LoadFromFile(path, loaded))
    {
        std::cerr << "[ProjectManager] Failed to load project: " << path << std::endl;
        return false;
    }

    if (m_project) delete m_project;
    m_project = new Project(std::move(loaded));
    m_projectPath = path;

    std::cout << "[ProjectManager] Project loaded: " << path << std::endl;
    return true;
}

bool ProjectManager::SaveProject(const std::string& path)
{
    if (!m_project)
        return false;

    if (!m_serializer.SaveToFile(path, *m_project))
    {
        std::cerr << "[ProjectManager] Failed to save project: " << path << std::endl;
        return false;
    }

    m_projectPath = path;

    std::cout << "[ProjectManager] Project saved: " << path << std::endl;
    return true;
}

bool ProjectManager::HasProjectPath() const
{
    return !m_projectPath.empty();
}

const std::string& ProjectManager::GetProjectPath() const
{
    return m_projectPath;
}

void ProjectManager::SetProjectPath(const std::string& path)
{
    m_projectPath = path;
}

Project* ProjectManager::GetProject()
{
    return m_project;
}

const Project* ProjectManager::GetProject() const
{
    return m_project;
}

} // namespace Editor::Project
