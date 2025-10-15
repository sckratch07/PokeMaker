#pragma once
#include "Project.hpp"
#include <string>
#include "nlohmann/json.hpp"

class Project;

class ProjectManager {
public:
    ProjectManager() = default;
    ~ProjectManager() = default;

    bool CreateProject(const std::string& name, const std::string& path);
    bool LoadProject(const std::string& path);
    bool SaveProject(const std::string& path);
    Project* GetCurrentProject();

private:
    Project currentProject;        // Projet actuellement chargé
};
