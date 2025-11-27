#ifndef _CORE_TILEMAP_HPP__
#define _CORE_TILEMAP_HPP__

#include "Core/Layer.hpp"
#include "Core/TileSet.hpp"
#include <nlohmann/json.hpp>
#include <string>
#include <vector>


namespace Core
{
/**
* @brief Représentation complète d'une map composée de layers et tilesets.
*/
struct TileMap
{
    std::string id; /**< Identifiant de la map */
    int width = 0; /**< Largeur en tiles */
    int height = 0; /**< Hauteur en tiles */
    std::vector<TileSet> tilesets; /**< Liste des tilesets référencés */
    std::vector<Layer> layers; /**< Layers (ordre de rendu) */
    std::map<std::string, nlohmann::json> properties; /**< Propriétés globales */


    /**
    * @brief Crée une TileMap vide de la taille donnée et avec un layer vide.
    */
    static TileMap MakeEmpty(const std::string& id, int width, int height);


    /**
    * @brief Vérifie la cohérence interne (taille des layers vs width*height).
    * @return true si valide.
    */
    bool Validate() const noexcept;


    /**
    * @brief Récupère un layer par nom (nullptr si introuvable).
    */
    Layer* GetLayerByName(const std::string& name);
    const Layer* GetLayerByNameConst(const std::string& name) const;
};


void to_json(nlohmann::json& j, const TileMap& m);
void from_json(const nlohmann::json& j, TileMap& m);


} // namespace core

#endif
