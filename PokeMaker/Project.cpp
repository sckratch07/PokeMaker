#include "Project.hpp"

Project::Project() : name(""), basePath("") {}

Project::Project(const std::string& name, const std::string& basePath) : name(name), basePath(basePath) {}

void Project::AddMap(Map& map)
{
    maps.push_back(map);
}

Map* Project::GetMap(const std::string& mapName)
{
    for (Map& map : maps)
    {
        if (map.GetName() == mapName)
        {
            return &map;
        }
    }
    return nullptr; // non trouvé
}

void Project::DeleteMap(int id)
{
    if (id != maps.size() - 1)
    {
        for (int i = id; i < maps.size() - 1; i++)
        {
            std::swap(maps[id], maps[id + 1]);
        }
    }
    maps.pop_back();
}

void Project::LoadTileset(const std::string& path, const sf::Vector2i& tileSize)
{
    Tileset* tileset = new Tileset;
    if (tileset->LoadFromFile(path, tileSize))
    {
        tilesets.push_back(tileset);
    }
}

Tileset* Project::GetTileset(int id)
{
    return tilesets[id];
}

void Project::DeleteTileset(int id)
{
    if (id < 0 || id >= tilesets.size()) return;

    for (Map& map : maps)
    {
        for (Layer& layer : map.GetLayers())
        {
            for (std::vector<Tile>& tiles : layer.GetTiles())
            {
                for (Tile& tile : tiles)
                {
                    if (tile.GetTilesetId() == id)
                        layer.SetTile(tile.GetPosition().x / tile.GetSize().x, tile.GetPosition().y / tile.GetSize().y, Tile());
                    else
                        tile.SetTilesetId(std::max(tile.GetTilesetId() - 1, 0));
                }
            }
        }
    }

    if (id != tilesets.size() - 1)
    {
        for (int i = id; i < tilesets.size() - 1; i++)
        {
            std::swap(tilesets[id], tilesets[id + 1]);
        }
    }

    delete tilesets.back();
    tilesets.pop_back();
}

void Project::AddLink(LinkMap& link)
{
    links.push_back(link);
}

void Project::DeleteLink(int id)
{
    if (id != links.size() - 1)
    {
        for (int i = id; i < links.size() - 1; i++)
        {
            std::swap(links[id], links[id + 1]);
        }
    }
    links.pop_back();
}

json Project::Serialize() const
{
    json j;
    j["name"] = name;
    j["basePath"] = basePath;

    j["tilesets"] = json::array();
    for (const auto& tileset : tilesets) {
        j["tilesets"].push_back(tileset->Serialize());
    }

    j["maps"] = json::array();
    for (const Map& map : maps)
    {
        j["maps"].push_back(map.Serialize());
    }

    j["links"] = json::array();
    for (const LinkMap& link : links)
    {
        j["links"].push_back(link.Serialize());
    }
    return j;
}

void Project::Deserialize(const json& jsonData)
{
    name = jsonData.value("name", "");
    basePath = jsonData.value("basePath", "");

    for (Tileset* tileset : tilesets) { delete tileset; }
    maps.clear();
    if (jsonData.contains("tilesets") && jsonData["tilesets"].is_array())
    {
        for (const auto& tilesetJson : jsonData["tilesets"])
        {
            Tileset* tileset = new Tileset;
            tileset->Deserialize(tilesetJson);
            tilesets.push_back(tileset);
        }
    }

    maps.clear();
    if (jsonData.contains("maps") && jsonData["maps"].is_array())
    {
        for (const auto& mapJson : jsonData["maps"])
        {
            Map map;
            map.Deserialize(mapJson, tilesets);
            maps.push_back(map);
        }
    }

    links.clear();
    if (jsonData.contains("links") && jsonData["links"].is_array())
    {
        for (const auto& linkJson : jsonData["links"])
        {
            LinkMap link;
            link.Deserialize(linkJson);
            links.push_back(link);
        }
    }
}
