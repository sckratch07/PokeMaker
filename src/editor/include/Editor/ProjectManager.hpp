#ifndef _EDITOR_PROJECTMANAGER_HPP__
#define _EDITOR_PROJECTMANAGER_HPP__

/**
 * @file ProjectManager.hpp
 * @brief Gère le projet actif : création, sauvegarde, chargement et état "dirty".
 *
 * Fournit des méthodes pour créer, ouvrir, sauvegarder, sauvegarder sous, ainsi
 * qu'un drapeau indiquant si le projet a été modifié (non sauvegardé).
 */

#include <memory>
#include <string>
#include "Project.hpp"

namespace Editor {

/**
 * @class ProjectManager
 * @brief Gestionnaire de projet pour l'éditeur.
 */
class ProjectManager
{
public:
    ProjectManager() = default;

    /** @brief Projet actuellement ouvert */
    std::shared_ptr<Project> activeProject;

    /** @brief Chemin du fichier courant si le projet est déjà sauvegardé (vide sinon) */
    std::string currentFilePath;

    /** @brief Indique si le projet a été modifié depuis la dernière sauvegarde */
    bool dirty = false;

    /** @brief Crée un nouveau projet */
    void createProject(const std::string& name);

    /** @brief Charge un projet depuis un fichier JSON */
    bool loadProject(const std::string& filePath);

    /**
     * @brief Sauvegarde le projet actif.
     * @return true si la sauvegarde a réussi.
     * Si currentFilePath est vide, la méthode retourne false — appeler saveProjectAs().
     */
    bool saveProject() const;

    /**
     * @brief Sauvegarde le projet actif sous un chemin donné et met à jour currentFilePath.
     * @return true si la sauvegarde a réussi.
     */
    bool saveProjectAs(const std::string& filePath);

    /** @brief Marquer le projet comme modifié (dirty = true) */
    void markDirty() { dirty = true; }

    /** @brief Marquer le projet comme non modifié (dirty = false) */
    void clearDirty() { dirty = false; }
};

} // namespace Editor

#endif
