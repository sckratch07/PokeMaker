#ifndef _CORE_PROJECT_HPP__
#define _CORE_PROJECT_HPP__

#include "Core/TileMap.hpp"
#include "Core/Tileset.hpp"

#include <string>
#include <vector>

namespace Core
{
    class Project
    {
    public:
        Project() = default;
        Project(std::string& name) : m_name(name) {}

        ~Project() = default;

        const std::string& GetName() const { return m_name; }
        const std::vector<TileMap>& GetMaps() const { return m_maps; }
        const std::vector<std::shared_ptr<Tileset>>& GetTilesets() const {return m_tilesets;}

        TileMap* GetMap(const std::string& mapName);
        std::shared_ptr<Tileset> GetTileset(const std::string& tilesetName);

        bool AddMap(TileMap& map);
        bool RemoveMap(const std::string& mapName);

        bool AddTileset(std::shared_ptr<Tileset>& tileset);
        bool RemoveTileset(const std::string& tilesetName);

    private:
        std::string m_name = "New Project";

        std::vector<TileMap> m_maps;
        std::vector<std::shared_ptr<Tileset>> m_tilesets;
    };
}

#endif