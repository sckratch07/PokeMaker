#ifndef _CORE_LAYER_HPP__
#define _CORE_LAYER_HPP__

#include "Tile.hpp"
#include <nlohmann/json.hpp>
#include <string>
#include <vector>


namespace Core
{
/**
* @brief Type de layer.
*/
enum class LayerType
{
    TileLayer = 0,
    ObjectLayer = 1
};


/**
* @brief Représente un layer dans une TileMap.
*
* Pour les TileLayer la taille du tableau `tiles` doit être width*height de la map.
* Pour ObjectLayer, `tiles` peut être vide et la liste d'objets (pas encore
* implémentée en détail dans ce module) doit être sérialisée via properties.
*/
struct Layer
{
    std::string name; /**< Nom du layer */
    LayerType type = LayerType::TileLayer; /**< Type du layer */
    std::vector<Tile> tiles; /**< Tableau de tiles (row-major) */
    std::map<std::string, nlohmann::json> properties; /**< Propriétés du layer */


    /**
    * @brief Obtient la tile à la position (x, y) en supposant row-major.
    * @param width largeur de la map pour calculer l'index.
    */
    const Tile& GetTileAt(int width, int x, int y) const;
    Tile& GetTileAt(int width, int x, int y);
};


void to_json(nlohmann::json& j, const Layer& l);
void from_json(const nlohmann::json& j, Layer& l);

} // namespace Core

#endif
