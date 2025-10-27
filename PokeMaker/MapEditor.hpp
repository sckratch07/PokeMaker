#pragma once
#include "Map.hpp"
#include "ProjectManager.hpp"
#include "Camera.hpp"

class MapEditor {
public:
    ~MapEditor();

    void NewMap(const std::string& name, const sf::Vector2i& size, const sf::Vector2i& tileSize, Project* currentProject);
    void LoadMap(const std::string& name, Project* currentProject);
    void DeleteLayer(int id);

    void Render(sf::RenderWindow& window);
    void UpdatePlace(float dt, sf::RenderWindow& window, Project* project, int selectedTile, int selectedLayer, int tilesetID);
    void UpdateCollision(float dt, sf::RenderWindow& window, Project* project, int selectedLayer);
    void DrawGrid(sf::RenderWindow& window);

    // Accesseurs
    void SetActiveMap(Map* map) { activeMap = map; }
    Map* GetActiveMap() const { return activeMap; }

private:
    Map* activeMap = nullptr;                  // carte actuellement éditée
};
