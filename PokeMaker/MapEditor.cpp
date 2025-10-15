#include "MapEditor.hpp"
#include <iostream>

void MapEditor::NewMap(const std::string& name, const sf::Vector2i& size, const sf::Vector2i& tileSize, ProjectManager& projectManager)
{
    Project* currentProject = projectManager.GetCurrentProject();

    Map newMap(name, size, tileSize);
    
    currentProject->AddMap(newMap);

    activeMap = &newMap;
    activeMap->AddLayer("Layer 0");

    std::cout << "[MapEditor] Nouvelle map : " << name << std::endl;
}

void MapEditor::LoadMap(const std::string& name, ProjectManager& projectManager)
{
    Project* currentProject = projectManager.GetCurrentProject();
    activeMap = currentProject->GetMap(name);

    std::cout << "[MapEditor] Chargement de la map : " << name << std::endl;
}

void MapEditor::Update(float dt)
{
    
}

void MapEditor::Render(sf::RenderWindow& window)
{
    if (!activeMap) return;

    activeMap->Render(window);

    // Dessiner la grille au-dessus des tiles si activé
    if (gridVisible) DrawGrid(window);

    // Dessiner collisions si activé
    if (showCollision) {
        for (auto& layer : activeMap->GetLayers())
        {
            // parcourir les tiles et dessiner un rectangle si collidable
            for (auto& row : layer.GetTiles())
            {
                for (auto& tile : row)
                {
                    if (tile.IsCollidable())
                    {
                        sf::RectangleShape rect(sf::Vector2f(tile.GetSize()));
                        rect.setPosition(sf::Vector2f(tile.GetPosition()));
                        rect.setFillColor(sf::Color(255, 0, 0, 100));
                        window.draw(rect);
                    }
                }
            }
        }
    }
}

void MapEditor::DrawGrid(sf::RenderWindow& window)
{
    if (!activeMap) return;

    sf::Vector2i size = activeMap->GetSize();
    sf::Vector2i tileSize = activeMap->GetTileSize();

    sf::VertexArray lines(sf::PrimitiveType::Lines);

    // Lignes verticales
    for (int x = 0; x <= size.x; ++x)
    {
        lines.append(sf::Vertex(sf::Vector2f((float)x * tileSize.x, 0.f), sf::Color(150, 150, 150)));
        lines.append(sf::Vertex(sf::Vector2f((float)(x * tileSize.x), (float)(size.y * tileSize.y)), sf::Color(150, 150, 150)));
    }

    // Lignes horizontales
    for (int y = 0; y <= size.y; ++y)
    {
        lines.append(sf::Vertex(sf::Vector2f(0.f, (float)y * tileSize.y), sf::Color(150, 150, 150)));
        lines.append(sf::Vertex(sf::Vector2f((float)(size.x * tileSize.x), (float)(y * tileSize.y)), sf::Color(150, 150, 150)));
    }

    window.draw(lines);
}
