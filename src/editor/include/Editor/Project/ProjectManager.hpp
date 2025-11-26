#ifndef _EDITOR_PROJECTMANAGER_HPP__
#define _EDITOR_PROJECTMANAGER_HPP__

/**
 * @file ProjectManager.hpp
 * @brief Gestion complète d’un projet de l’éditeur.
 */

#include <string>
#include <vector>
#include <memory>

#include <SFML/System/Clock.hpp>

#include "Editor/Project/Project.hpp"
#include "Editor/Project/ProjectSerializer.hpp"

namespace Editor::Project {

/**
 * @class ProjectManager
 * @brief Gère la création, le chargement et la sauvegarde d’un projet.
 */
class ProjectManager
{
public:
    ProjectManager();
    ~ProjectManager();

    /// Met à jour les éléments du projet (maps, NPC, etc.)
    void Update(float dt);

    /// Crée un projet vide
    void CreateEmptyProject();

    /// Charge un projet depuis un fichier JSON
    bool LoadProject(const std::string& path);

    /// Sauvegarde un projet dans son emplacement actuel
    bool SaveProject(const std::string& path);

    /// Permet de savoir si le projet a un chemin de sauvegarde
    bool HasProjectPath() const;

    /// Retourne le chemin du projet
    const std::string& GetProjectPath() const;

    /// Modifie le chemin actuel du projet
    void SetProjectPath(const std::string& path);

    /// Retourne le projet en cours d’édition
    Project* GetProject();
    const Project* GetProject() const;

private:
    Project* m_project = nullptr;
    std::string m_projectPath;
    ProjectSerializer m_serializer;
};

} // namespace Editor::Project

#endif // _EDITOR_PROJECTMANAGER_HPP__
