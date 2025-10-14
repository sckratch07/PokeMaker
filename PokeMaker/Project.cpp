#include "Project.hpp"

Project::Project() : name(""), basePath("") {}

Project::Project(const std::string& name, const std::string& basePath) : name(name), basePath(basePath) {}

void Project::AddMap(const Map& map)
{
    maps.push_back(map);
}

Map* Project::GetMap(const std::string& mapName)
{
    for (auto& map : maps)
    {
        if (map.GetName() == mapName)
        {
            return &map;
        }
    }
    return nullptr; // non trouvé
}

json Project::Serialize() const
{
    json j;
    j["name"] = name;
    j["basePath"] = basePath;

    // Sérialisation des maps
    j["maps"] = json::array();
    for (const auto& map : maps)
    {
        j["maps"].push_back(map.Serialize());
    }

    // Sérialisation des tilesets
    j["tilesets"] = json::array();
    for (const auto& tileset : tilesets)
    {
        j["tilesets"].push_back(tileset.Serialize());
    }

    return j;
}

void Project::Deserialize(const json& jsonData)
{
    name = jsonData.value("name", "");
    basePath = jsonData.value("basePath", "");

    maps.clear();
    if (jsonData.contains("maps") && jsonData["maps"].is_array())
    {
        for (const auto& mapJson : jsonData["maps"])
        {
            Map map;
            map.Deserialize(mapJson);
            maps.push_back(map);
        }
    }

    tilesets.clear();
    if (jsonData.contains("tilesets") && jsonData["tilesets"].is_array())
    {
        for (const auto& tilesetJson : jsonData["tilesets"])
        {
            Tileset tileset;
            tileset.Deserialize(tilesetJson);
            tilesets.push_back(tileset);
        }
    }
}
