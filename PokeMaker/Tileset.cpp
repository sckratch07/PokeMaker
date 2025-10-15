#include "Tileset.hpp"
#include <iostream>

Tileset::Tileset() : name(""), tileSize(32, 32), columns(0), rows(0) {}

bool Tileset::LoadFromFile(const std::string& path)
{
    if (!texture.loadFromFile(path)) {
        std::cerr << "[Tileset] Impossible de charger la texture : " << path << std::endl;
        return false;
    }

    name = path;

    // Calcul des colonnes et lignes en fonction de la taille de la texture
    if (tileSize.x > 0 && tileSize.y > 0) {
        columns = texture.getSize().x / tileSize.x;
        rows = texture.getSize().y / tileSize.y;
    }

    return true;
}

sf::IntRect Tileset::GetTileTextureRect(int id) const
{
    if (columns == 0) return sf::IntRect({ 0, 0 }, { 0, 0 });

    int x = (id % columns) * tileSize.x;
    int y = (id / columns) * tileSize.y;
    return sf::IntRect({ x, y }, { tileSize.x, tileSize.y });
}

json Tileset::Serialize() const
{
    json j;
    j["name"] = name;
    j["tileSize"] = { tileSize.x, tileSize.y };
    j["columns"] = columns;
    j["rows"] = rows;
    return j;
}

void Tileset::Deserialize(const json& jsonData)
{
    name = jsonData.value("name", "");
    if (jsonData.contains("tileSize") && jsonData["tileSize"].is_array() && jsonData["tileSize"].size() == 2) {
        tileSize.x = jsonData["tileSize"][0];
        tileSize.y = jsonData["tileSize"][1];
    }
    columns = jsonData.value("columns", 0);
    rows = jsonData.value("rows", 0);

    if (!name.empty()) {
        if (!texture.loadFromFile(name)) {
            std::cerr << "[Tileset] Impossible de charger la texture depuis : " << name << std::endl;
        }
    }
}
