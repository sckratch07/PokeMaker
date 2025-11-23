#include "ProjectManager.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

namespace Editor {

void ProjectManager::createProject(const std::string& name)
{
    activeProject = std::make_shared<Project>(name);
    currentFilePath.clear();
    dirty = true; // nouveau projet non sauvegardé
}

bool ProjectManager::loadProject(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open()) return false;

    nlohmann::json j;
    try
    {
        file >> j;
    } catch (...)
    {
        return false;
    }

    activeProject = std::make_shared<Project>();
    try
    {
        activeProject->fromJson(j);
    } catch (...)
    {
        activeProject.reset();
        return false;
    }

    currentFilePath = filePath;
    dirty = false;
    return true;
}

bool ProjectManager::saveProject() const
{
    if (!activeProject) return false;
    if (currentFilePath.empty()) return false;

    std::ofstream file(currentFilePath);
    if (!file.is_open()) return false;

    try
    {
        file << activeProject->toJson().dump(4);
    } catch (...)
    {
        return false;
    }
    return true;
}

bool ProjectManager::saveProjectAs(const std::string& filePath)
{
    if (!activeProject) return false;

    std::ofstream file(filePath);
    if (!file.is_open()) return false;

    try
    {
        file << activeProject->toJson().dump(4);
    } catch (...)
    {
        return false;
    }

    currentFilePath = filePath;
    return true;
}

} // namespace Editor
