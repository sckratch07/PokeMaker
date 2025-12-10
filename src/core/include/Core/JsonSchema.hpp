#ifndef _CORE_JSONSCHEMA_HPP__
#define _CORE_JSONSCHEMA_HPP__

#include "Core/Project.hpp"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace Core
{
    #pragma region Project
    void to_json(json& j, const Project& project)
    {
        j["name"] = project.GetName();
        j["maps"] = project.GetMaps();
        j["tilesets"] = project.GetTilesets();
    }

    void from_json(const json& j, Project& project)
    {
        project = Project(j.value("name", "New Project"));

        if (j.contains("tilesets") && j["tilesets"].is_array())
        {
            for (const auto& tilesetsJson : j["tilesets"])
            {
                std::shared_ptr<Tileset> tileset = std::make_shared<Tileset>();
                from_json(tilesetsJson, tileset);
                project.AddTileset(tileset);
            }
        }
        if (j.contains("maps") && j["maps"].is_array())
        {
            for (const auto& mapsJson : j["maps"])
            {
                TileMap tilemap;
                from_json(mapsJson, tilemap, project.GetTilesets());
                project.AddMap(tilemap);
            }
        }
    }
    #pragma endregion

    #pragma region Tilemap
    void to_json(json& j, const TileMap& tilemap)
    {
        j["name"] = tilemap.m_name;
        j["width"] = tilemap.m_width;
        j["height"] = tilemap.m_height;
        j["tileWidth"] = tilemap.m_tileWidth;
        j["tileHeight"] = tilemap.m_tileHeight;
        j["layers"] = tilemap.m_layers;
    }

    void from_json(const json& j, TileMap& tilemap, const std::vector<std::shared_ptr<Tileset>>& tilesets)
    {
        tilemap.m_name = j.value("name", "Unnamed Map");
        tilemap.m_width = j.value("width", 0);
        tilemap.m_height = j.value("height", 0);
        tilemap.m_tileWidth = j.value("tileWidth", 0);
        tilemap.m_tileHeight = j.value("tileHeight", 0);
        
        if (j.contains("layers") && j["layers"].is_array())
        {
            for (const auto& layerJson : j["layers"])
            {
                Layer layer;
                from_json(layerJson, layer, tilesets);
                tilemap.m_layers.push_back(layer);
            }
        }
    }
    #pragma endregion

    #pragma region Layer
    void to_json(json& j, const Layer& layer)
    {
        j["name"] = layer.m_name;
        j["width"] = layer.m_width;
        j["height"] = layer.m_height;
        j["tiles"] = layer.m_tiles;
    }

    void from_json(const json& j, Layer& layer, const std::vector<std::shared_ptr<Tileset>>& tilesets)
    {
        layer.m_name = j.value("name", "Unnamed Layer");
        layer.m_width = j.value("width", 0);
        layer.m_height = j.value("height", 0);
        
        if (j.contains("tiles") && j["tiles"].is_array())
        {
            for (const auto& tileJson : j["tiles"])
            {
                Tile tile;
                from_json(tileJson, tile, tilesets);
                layer.m_tiles.push_back(tile);
            }
        }
    }
    #pragma endregion

    #pragma region Tile
    void to_json(json& j, const Tile& tile)
    {
        j["type"] = tile.m_type;
        j["posX"] = tile.m_x;
        j["posY"] = tile.m_y;
        j["width"] = tile.m_width;
        j["height"] = tile.m_height;
        j["tileset"] = tile.m_tileset->m_name;
        j["tileIndex"] = tile.m_tileIndex;
    }

    void from_json(const json& j, Tile& tile, const std::vector<std::shared_ptr<Tileset>>& tilesets)
    {
        tile.m_type = j.value("type", EMPTY);
        tile.m_x = j.value("posX", 0);
        tile.m_y = j.value("posY", 0);
        tile.m_width = j.value("width", 0);
        tile.m_height = j.value("height", 0);
        
        if (j.contains("tileset") && j["tileset"].is_array())
        {
            std::string tilesetName = j.value("tileset", "");
            for (const auto& tileset : tilesets)
            {
                if (tileset->m_name == tilesetName)
                {
                    tile.m_tileset = tileset;
                    tile.m_tileIndex = j.value("tileIndex", 0);
                    break;
                }
            }
        }
    }
    #pragma endregion

    #pragma region Tileset
    void to_json(json& j, const std::shared_ptr<Tileset>& tileset)
    {
        j["name"] = tileset->m_name;
        j["imagePath"] = tileset->m_imagePath;
        j["tileWidth"] = tileset->m_tileWidth;
        j["tileHeight"] = tileset->m_tileHeight;
    }

    void from_json(const json& j, std::shared_ptr<Tileset>& tileset)
    {
        tileset->m_name = j.value("name", "Unnamed Tileset");
        tileset->m_imagePath = j.value("imagePath", "");
        tileset->m_tileWidth = j.value("tileWidth", 0);
        tileset->m_tileHeight = j.value("tileHeight", 0);
    }
    #pragma endregion
}

#endif