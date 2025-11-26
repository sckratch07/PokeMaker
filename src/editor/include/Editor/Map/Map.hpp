#ifndef _EDITOR_MAP_HPP__
#define _EDITOR_MAP_HPP__

/**
 * @file Map.hpp
 * @brief Wrapper haut-niveau d'une map : descriptor + TileMap + helpers IO.
 *
 * Map propose :
 *  - Chargement / sauvegarde via JSON (conforme ProjectSerializer expectations)
 *  - Accès au TileMap pour rendu / édition
 *  - Gestion des "portals" (warps) entre maps (basic)
 */

#include <string>
#include <vector>
#include <unordered_map>

#include "Editor/Map/TileMap.hpp"
#include "Editor/Project/Project.hpp"
#include <nlohmann/json.hpp>

namespace Editor::Map {

/**
 * @struct Portal
 * @brief Pont entre deux maps (entrée/sortie).
 */
struct Portal
{
    std::string id;
    std::string targetMap; // relative path to target
    int srcX = 0;
    int srcY = 0;
    int dstX = 0;
    int dstY = 0;
};

class Map
{
public:
    Map() = default;
    Map(const Project::MapDescriptor& desc);

    const Project::MapDescriptor& GetDescriptor() const;
    Project::MapDescriptor& GetDescriptor();

    TileMap& GetTileMap();
    const TileMap& GetTileMap() const;

    /// Load map from its descriptor.relativePath (joined with rootPath)
    bool LoadFromFile(const std::string& rootPath);

    /// Save map to its descriptor.relativePath (joined with rootPath)
    bool SaveToFile(const std::string& rootPath) const;

    /// Add / remove portals
    void AddPortal(const Portal& p);
    bool RemovePortalById(const std::string& id);
    std::vector<Portal> GetPortals() const;

    /// Convenience: regenerate TileMap from descriptor size
    void RebuildTileMapFromDescriptor();

private:
    Project::MapDescriptor m_descriptor;
    TileMap m_tileMap;
    std::vector<Portal> m_portals;
};

} // namespace Editor::Map

#endif // _EDITOR_MAP_HPP__
