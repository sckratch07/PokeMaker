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
        Project(const char* name) : m_name(name) {}

        ~Project() = default;

        const std::string& GetName() const { return m_name; }
        const std::vector<TileMap> GetMaps() const {return m_maps; }
        const std::vector<Tileset> GetTilesets() const {return m_tilesets;}

        TileMap* GetMap(const std::string& mapName);
        Tileset* GetTileset(const std::string& tilesetName);

        bool AddMap(TileMap& map);
        bool RemoveMap(const std::string& mapName);

        bool AddTileset(Tileset& tileset);
        bool RemoveTileset(const std::string& tilesetName);

    private:
        std::string m_name;

        std::vector<TileMap> m_maps;
        std::vector<Tileset> m_tilesets;
    };
}

#endif