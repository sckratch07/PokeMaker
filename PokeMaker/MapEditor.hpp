#pragma once
#include <SFML/Graphics.hpp>
#include "Map.hpp"
#include "ProjectManager.hpp"
#include "UIManager.hpp"
#include "Camera.hpp"

class MapEditor {
public:
    ~MapEditor();

    void NewMap(const std::string& name, const sf::Vector2i& size, const sf::Vector2i& tileSize, ProjectManager& projectManager);
    void LoadMap(const std::string& name, ProjectManager& projectManager);

    void LoadTileset(std::string path, const sf::Vector2i& tileSize);

    void Render(sf::RenderWindow& window);
    void Update(float dt, sf::RenderWindow& window, UIManager& uiManager, Camera& camera);
    void DrawGrid(sf::RenderWindow& window);

    // Accesseurs
    void SetActiveMap(Map* map) { activeMap = map; }
    Map* GetActiveMap() const { return activeMap; }
    int* GetActiveTilesets() { return &activeTilesetIndex; }

private:
    Map* activeMap = nullptr;                  // carte actuellement éditée
    int activeTilesetIndex = 0;
};
