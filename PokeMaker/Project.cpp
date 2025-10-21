#include "Project.hpp"

Project::Project() : name(""), basePath("") {}

Project::Project(const std::string& name, const std::string& basePath) : name(name), basePath(basePath) {}

void Project::AddMap(Map* map)
{
    maps.push_back(map);
}

Map* Project::GetMap(const std::string& mapName)
{
    for (Map* map : maps)
    {
        if (map->GetName() == mapName)
        {
            return map;
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
    for (Map* map : maps)
    {
        j["maps"].push_back(map->Serialize());
    }
    return j;
}

void Project::Deserialize(const json& jsonData)
{
    name = jsonData.value("name", "");
    basePath = jsonData.value("basePath", "");

    for (Map* map : maps) { delete map; }
    maps.clear();
    if (jsonData.contains("maps") && jsonData["maps"].is_array())
    {
        for (const auto& mapJson : jsonData["maps"])
        {
            Map* map = new Map;
            map->Deserialize(mapJson);
            maps.push_back(map);
        }
    }
}
