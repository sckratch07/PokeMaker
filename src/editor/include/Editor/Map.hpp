#ifndef _EDITOR_MAP_HPP__
#define _EDITOR_MAP_HPP__

/**
 * @file Map.hpp
 * @brief Structure logique d'une map (layers, tilesets, metadata).
 *
 * Cette classe ne gère :
 *  - ni le rendu (géré par TileMapRenderer / GridRenderer)
 *  - ni les I/O JSON (géré par MapSerializer)
 *
 * Elle représente uniquement les données nécessaires à l’éditeur.
 */

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include <SFML/System/Vector2.hpp>

#include "Editor/TileLayer.hpp"
#include "Editor/TileSet.hpp"
#include "Editor/NPC/NPC.hpp"

namespace Editor {

/**
 * @enum MapType
 * @brief Différencie maps extérieures, intérieures (donjons), etc.
 */
enum class MapType
{
    Outdoor,
    Indoor
};

/**
 * @class Map
 * @brief Représentation logique d’une map.
 */
class Map
{
public:
    Map();
    ~Map() = default;

    // ---- Métadonnées générales ----
    std::string name;
    MapType type;

    sf::Vector2u size; ///< Dimensions de la map en tiles

    // ---- Tilesets & Layers ----
    std::vector<TileSet> tilesets;
    std::vector<TileLayer> layers;

    // ---- NPC ----
    std::vector<NPC> npcs;

    // ---- Propriétés custom ----
    std::unordered_map<std::string, std::string> properties;

    // ---- Utilitaires ----
    void AddLayer(const TileLayer& layer);
    void RemoveLayer(size_t index);

    TileLayer* GetLayer(const std::string& name);
    const TileLayer* GetLayer(const std::string& name) const;

    TileSet* GetTilesetByName(const std::string& name);
    const TileSet* GetTilesetByName(const std::string& name) const;

    void Clear();

    // ---- Validation ----
    bool IsValid() const;

private:
    // rien pour le moment
};

} // namespace Editor

#endif // _EDITOR_MAP_HPP__
