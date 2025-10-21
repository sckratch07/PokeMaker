#pragma once
#include "Project.hpp"

class Project;

class ProjectManager {
public:
    ProjectManager() : newProject(false) {};

    bool CreateProject(const std::string& name, const std::string& path);
    bool LoadProject(const std::string& path);
    bool SaveProject(const std::string& path);

    void ProjectIsLoaded(bool isLoad) { newProject = isLoad; }
    bool& IsNewProject() { return newProject; }
    Project* GetCurrentProject() { return &currentProject; }

private:
    Project currentProject;        // Projet actuellement chargé
    bool newProject;
};
