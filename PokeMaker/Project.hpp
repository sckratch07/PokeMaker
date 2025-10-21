#pragma once
#include <iostream>
#include "Map.hpp"

class Project {
public:
    Project();
    Project(const std::string& name, const std::string& basePath);

    void AddMap(Map* map);
    Map* GetMap(const std::string& name);

    json Serialize() const;
    void Deserialize(const json& jsonData);

    // Accesseurs
    std::string& GetName() { return name; }
    std::string& GetBasePath() { return basePath; }
    std::vector<Map*>& GetMaps() { return maps; }

private:
    std::string name;
    std::string basePath;
    std::vector<Map*> maps;
};
