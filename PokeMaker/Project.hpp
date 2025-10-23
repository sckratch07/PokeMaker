#pragma once
#include <iostream>
#include "Map.hpp"
#include "LinkMap.hpp"

class Project {
public:
    Project();
    Project(const std::string& name, const std::string& basePath);
    
    void AddMap(Map* map);
    Map* GetMap(const std::string& name);
    void DeleteMap(int id);

    void LoadTileset(const std::string& path, const sf::Vector2i& tileSize);
    Tileset* GetTileset(int id);
    void DeleteTileset(int id);

    void AddLink(LinkMap& link);
    void DeleteLink(int id);

    json Serialize() const;
    void Deserialize(const json& jsonData);

    // Accesseurs
    std::string& GetName() { return name; }
    std::string& GetBasePath() { return basePath; }
    std::vector<Map*>& GetMaps() { return maps; }
    std::vector<Tileset*>& GetTilesets() { return tilesets; }
    std::vector<LinkMap>& GetLinks() { return links; }

private:
    std::string name;
    std::string basePath;
    std::vector<Map*> maps;
    std::vector<Tileset*> tilesets;
    std::vector<LinkMap> links;
};
