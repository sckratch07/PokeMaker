#ifndef _CORE_TILESET_HPP__
#define _CORE_TILESET_HPP__

#include <nlohmann/json.hpp>
#include <string>


namespace Core
{
/**
* @brief Métadonnées d'un tileset.
*
* Le tileset est décrit par un identifiant (utilisé dans les Tile) et un chemin
* relatif vers l'image source. Le Core ne charge pas la texture : cela reste
* la responsabilité du Renderer ou d'un ResourceManager spécialisé.
*/
struct TileSet
{
    std::string id; /**< Identifiant unique */
    std::string path; /**< Chemin relatif vers l'image du tileset */
    int tile_width = 32; /**< Largeur d'une tuile en pixels */
    int tile_height = 32; /**< Hauteur d'une tuile en pixels */
    int columns = 0; /**< Colonnes dans l'image (optionnel) */


    bool operator==(const TileSet& o) const noexcept
    {
        return id == o.id && path == o.path &&
            tile_width == o.tile_width && tile_height == o.tile_height;
    }
};

void to_json(nlohmann::json& j, const TileSet& t);
void from_json(const nlohmann::json& j, TileSet& t);

} // namespace Core

#endif
