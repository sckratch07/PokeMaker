#include "Core/Project.hpp"
#include <iostream>

namespace Core
{
    TileMap* Project::GetMap(const std::string& mapName)
    {
        for (auto& map : m_maps)
        {
            if (map.m_name == mapName)
            {
                return &(map);
            }
        }
        return nullptr;
    }

    Tileset* Project::GetTileset(const std::string& tilesetName)
    {
        for (auto& tileset : m_tilesets)
        {
            if (tileset.m_name == tilesetName)
            {
                return &tileset;
            }
        }
        return nullptr;
    }


    bool Project::AddMap(TileMap& map)
    {
        m_maps.push_back(map);
        return true;
    }

    bool Project::RemoveMap(const std::string& mapName)
    {
        for (auto& map : m_maps)
        {
            if (map.m_name == mapName)
            {
                std::swap(map, m_maps.back());
                m_maps.pop_back();
                return true;
            }
        }
        return false;
    }

    bool Project::AddTileset(Tileset& tileset)
    {
        m_tilesets.push_back(tileset);
        return true;
    }

    bool Project::RemoveTileset(const std::string& tilesetName)
    {
        for (auto& tileset : m_tilesets)
        {
            if (tileset.m_name == tilesetName)
            {
                std::swap(tileset, m_tilesets.back());
                m_tilesets.pop_back();
                return true;
            }
        }
        return false;
    }
}