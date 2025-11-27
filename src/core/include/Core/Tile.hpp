#ifndef _CORE_TILE_HPP__
#define _CORE_TILE_HPP__

#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include <map>
#include <optional>


namespace Core
{
/**
* @brief Représente une unique frame d'animation pour une tile.
*/
struct TileFrame
{
    std::string tileset_id; /**< Identifiant du tileset */
    int tile_index = -1; /**< Index de la tuile dans le tileset */
    int duration_ms = 100; /**< Durée d'affichage de cette frame (ms) */
};


/**
* @brief Représente un tile (peut être statique ou animé) placé sur la map.
*
* Les propriétés sont stockées dans un objet JSON pour permettre l'extension
* facile (scripts, flags custom, collisions, etc.).
*/
struct Tile
{
    std::string tileset_id; /**< Identifiant du tileset */
    int tile_index = -1; /**< Index de la tuile dans le tileset */
    std::map<std::string, nlohmann::json> properties; /**< Propriétés custom */


    // Animation : si frames n'est pas vide, la tile est animée.
    std::vector<TileFrame> frames;
    bool loop = true; /**< Boucler l'animation si animée */


    /**
    * @brief Indique si la tile a une animation associée.
    */
    bool IsAnimated() const noexcept { return !frames.empty(); }
};


// Sérialisation JSON
void to_json(nlohmann::json& j, const TileFrame& f);
void from_json(const nlohmann::json& j, TileFrame& f);


void to_json(nlohmann::json& j, const Tile& t);
void from_json(const nlohmann::json& j, Tile& t);


} // namespace Core

#endif //*!_CORE_TILE_HPP__