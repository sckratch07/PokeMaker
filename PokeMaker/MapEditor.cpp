#include "MapEditor.hpp"

MapEditor::~MapEditor()
{
    delete activeMap;
}

void MapEditor::NewMap(const std::string& name, const sf::Vector2i& size, const sf::Vector2i& tileSize, Project* currentProject)
{
    activeMap = new Map(name, size, tileSize);
    currentProject->AddMap(activeMap);
    activeMap->AddLayer("Layer 0");
}

void MapEditor::LoadMap(const std::string& name, Project* currentProject)
{
    activeMap = currentProject->GetMap(name);
}

void MapEditor::DeleteLayer(int id)
{
    std::vector<Layer>& layers = activeMap->GetLayers();
    if (id != layers.size() - 1)
    {
        for (int i = id; i < layers.size() - 1; i++)
        {
            std::swap(layers[id], layers[id + 1]);
        }
    }
    layers.pop_back();
}

void MapEditor::Render(sf::RenderWindow& window, bool& collisionMode, int& selectedLayer)
{
    if (!activeMap) return;

    activeMap->Render(window, collisionMode, selectedLayer);
    DrawGrid(window);
}

void MapEditor::UpdatePlace(float dt, sf::RenderWindow& window, Project* project, int selectedTile, int selectedLayer, int tilesetID)
{
    if (!activeMap || tilesetID >= project->GetTilesets().size() || tilesetID < 0) return;

    // Conversion de la position souris en coordonnées map
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(mousePos, window.getView());
    sf::Vector2i tilePos(
        static_cast<int>(worldPos.x / activeMap->GetTileSize().x),
        static_cast<int>(worldPos.y / activeMap->GetTileSize().y));

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) &&
        selectedTile >= 0 && tilePos.x >= 0 && tilePos.y >= 0)
    {
        if (selectedLayer < activeMap->GetLayers().size())
        {
            Layer& layer = activeMap->GetLayer(selectedLayer);

            Tileset* tileset = project->GetTileset(tilesetID);

            sf::IntRect texRect = tileset->GetTileTextureRect(selectedTile);
            Tile newTile(
                activeMap->GetTileSize(), sf::Vector2i(tilePos.x * activeMap->GetTileSize().x, tilePos.y * activeMap->GetTileSize().y),
                tileset->GetTexture(), texRect, tilesetID
            );

            layer.SetTile(tilePos.x, tilePos.y, newTile);
        }
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) &&
        selectedTile >= 0 && tilePos.x >= 0 && tilePos.y >= 0)
    {
        Layer& layer = activeMap->GetLayer(selectedLayer);
        layer.SetTile(tilePos.x, tilePos.y, Tile());
    }
}

void MapEditor::UpdateCollision(float dt, sf::RenderWindow& window, Project* project, int selectedLayer)
{
    if (!activeMap) return;

    // Conversion de la position souris en coordonnées map
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(mousePos, window.getView());
    sf::Vector2i tilePos(
        static_cast<int>(worldPos.x / activeMap->GetTileSize().x),
        static_cast<int>(worldPos.y / activeMap->GetTileSize().y));

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && tilePos.x >= 0 && tilePos.y >= 0)
    {
        Layer& layer = activeMap->GetLayer(selectedLayer);
        Tile* tile = layer.GetTile(tilePos.x, tilePos.y);
        if (tile) tile->SetCollidable(true);
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && tilePos.x >= 0 && tilePos.y >= 0)
    {
        Layer& layer = activeMap->GetLayer(selectedLayer);
        Tile* tile = layer.GetTile(tilePos.x, tilePos.y);
        if (tile) tile->SetCollidable(false);
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
