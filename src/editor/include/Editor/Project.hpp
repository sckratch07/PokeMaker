#ifndef _EDITOR_PROJECT_HPP__
#define _EDITOR_PROJECT_HPP__

/**
 * @file Project.hpp
 * @brief Représentation d'un projet d'édition complet.
 *
 * Un projet contient plusieurs maps, un nom, et peut être sauvegardé/chargé via JSON.
 */

#include "Editor/Map.hpp"
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include <memory>

namespace Editor {

/**
 * @class Project
 * @brief Représente un projet PokeMaker contenant des maps et des ressources.
 */
class Project
{
public:
    Project() = default;
    explicit Project(const std::string& name);

    /** @brief Nom du projet */
    std::string name;

    /** @brief Liste des maps du projet */
    std::vector<std::shared_ptr<Map>> maps;

    /**
     * @brief Récupère une map par son nom.
     * @return pointeur ou nullptr si introuvable.
     */
    std::shared_ptr<Map> getMap(const std::string& mapName);

    /** @brief Convertit le projet vers JSON */
    nlohmann::json toJson() const;

    /** @brief Charge le projet depuis JSON */
    void fromJson(const nlohmann::json& j);
};

} // namespace Editor

#endif
