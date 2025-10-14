#pragma once
#include <SFML/Graphics.hpp>
#include "Map.hpp"
#include "ProjectManager.hpp"

class MapEditor {
public:
    MapEditor() = default;
    MapEditor(ProjectManager& projectManager);

    void NewMap(const std::string& name, const sf::Vector2i& size, const sf::Vector2i& tileSize);
    void LoadMap(const std::string& name);

    void Render(sf::RenderWindow& window);
    void Update(float dt);
    void DrawGrid(sf::RenderWindow& window);

    // Accesseurs
    void SetActiveMap(Map* map) { activeMap = map; }
    Map* GetActiveMap() const { return activeMap; }
    void SetGridVisible(bool visible) { gridVisible = visible; }
    void SetShowCollision(bool show) { showCollision = show; }

private:
    Map* activeMap = nullptr;                  // carte actuellement éditée
    ProjectManager projectManager;             // Pour liste de map
    bool gridVisible;
    bool showCollision;
};
