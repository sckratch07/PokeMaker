#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>
#include "Map.hpp"
#include "Tileset.hpp"

using json = nlohmann::json;

class Project {
public:
    Project();
    Project(const std::string& name, const std::string& basePath);

    void AddMap(const Map& map);
    Map* GetMap(const std::string& name);

    json Serialize() const;
    void Deserialize(const json& jsonData);

    // Accesseurs
    const std::string& GetName() const { return name; }
    const std::string& GetBasePath() const { return basePath; }
    const std::vector<Map>& GetMaps() const { return maps; }
    const std::vector<Tileset>& GetTilesets() const { return tilesets; }

private:
    std::string name;
    std::string basePath;
    std::vector<Map> maps;
    std::vector<Tileset> tilesets;
};
