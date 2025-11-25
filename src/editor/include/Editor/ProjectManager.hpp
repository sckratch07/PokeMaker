#ifndef _EDITOR_PROJECTMANAGER_HPP__
#define _EDITOR_PROJECTMANAGER_HPP__

/**
 * @file ProjectManager.hpp
 * @brief Gestion des projets : création, ouverture, sauvegarde, UI.
 *
 * Un projet contient :
 * - un dossier racine
 * - un fichier Project.json
 * - un dossier Maps/ contenant les fichiers .map.json
 *
 * Le ProjectManager orchestre l'accès aux maps et aux ressources
 * (via ResourceCache) et appelle MapSerializer pour charger/sauver.
 */

#include <string>
#include <vector>
#include <memory>

#include <SFML/System/Time.hpp>
#include <nlohmann/json.hpp>

#include "Editor/ResourceCache.hpp"
#include "Editor/Map.hpp"
#include "Editor/MapSerializer.hpp"

namespace Editor {

/**
 * @class ProjectManager
 * @brief Responsable de la gestion complète d’un projet d’édition.
 */
class ProjectManager
{
public:
    /// Structure représentant les données d’un projet
    struct ProjectData {
        std::string name;
        std::string rootPath;
        std::string resourcesPath;
        std::vector<std::string> mapFiles;
        bool valid = false;
    };

public:
    explicit ProjectManager(ResourceCache* resourceCache);
    ~ProjectManager() = default;

    // ---- Cycle de vie projet ----
    bool CreateNewProject();
    bool OpenProjectDialog();
    bool OpenProject(const std::string& projectPath);
    bool SaveCurrentProject();
    bool SaveProjectAs(const std::string& path);

    inline bool HasProject() const { return m_currentProject.valid; }

    // ---- Gestion des maps ----
    bool LoadMap(const std::string& mapFile);
    bool CreateNewMap(const std::string& name);
    bool SaveMap(Map& map);

    const ProjectData& GetProjectData() const { return m_currentProject; }

    // ---- Update & UI ----
    void Update(sf::Time dt);
    void RenderUI();

private:
    // helpers internes
    bool LoadProjectJson(const std::string& file);
    bool SaveProjectJson(const std::string& file);
    std::string OpenFileDialog(const char* filter);
    std::string OpenFolderDialog();
    std::string SaveFileDialog(const char* filter);

private:
    ResourceCache* m_resourceCache;
    ProjectData m_currentProject;

    // Map courante en édition
    std::unique_ptr<Map> m_currentMap;
    std::string m_loadedMapFile;

    // UI
    bool m_showProjectWindow = true;
    char m_tmpProjectName[128] = "Project";
    char m_tmpMapName[128] = "DefaultMap";
};

} // namespace Editor

#endif // _EDITOR_PROJECTMANAGER_HPP__
