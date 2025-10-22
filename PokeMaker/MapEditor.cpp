#include "MapEditor.hpp"

MapEditor::~MapEditor()
{
    delete activeMap;
}

void MapEditor::NewMap(const std::string& name, const sf::Vector2i& size, const sf::Vector2i& tileSize, ProjectManager& projectManager)
{
    Project* currentProject = projectManager.GetCurrentProject();

    activeMap = new Map(name, size, tileSize);
    currentProject->AddMap(activeMap);
    activeMap->AddLayer("Layer 0");

    std::cout << "[MapEditor] Nouvelle map : " << name << std::endl;
}

void MapEditor::LoadMap(const std::string& name, ProjectManager& projectManager)
{
    if (activeMap) delete activeMap;
    Project* currentProject = projectManager.GetCurrentProject();
    activeMap = currentProject->GetMap(name);

    std::cout << "[MapEditor] Chargement de la map : " << name << std::endl;
}

void MapEditor::LoadTileset(std::string& path, const sf::Vector2i& tileSize)
{
    if (!activeMap) return;
    
    Tileset* newTileset = new Tileset;
    if (newTileset->LoadFromFile(path, tileSize))
    {
        activeMap->AddTileset(newTileset);
        activeTilesetIndex = static_cast<int>(activeMap->GetTilesets().size() - 1);
        std::cout << "[MapEditor] Tileset ajoute : " << path << std::endl;
    }
}

void MapEditor::DeleteTileset(int id)
{
    std::vector<Tileset*>& tilesets = activeMap->GetTilesets();
    if (id < 0 || id >= tilesets.size()) return;

    for (Layer& layer : activeMap->GetLayers())
    {
        for (std::vector<Tile>& tiles : layer.GetTiles())
        {
            for (Tile& tile : tiles)
            {
                if (tile.GetTilesetId() == id)
                    layer.SetTile(tile.GetPosition().x / tile.GetSize().x, tile.GetPosition().y / tile.GetSize().y,  Tile());
                else
                    tile.SetTilesetId(std::max(tile.GetTilesetId() - 1, 0));
            }
        }
    }

    if (id != tilesets.size() - 1)
    {
        for (int i = id; i < tilesets.size() - 1; i++)
        {
            std::swap(tilesets[id], tilesets[id + 1]);
        }
    }

    delete tilesets.back();
    tilesets.pop_back();
    activeTilesetIndex = std::max(activeTilesetIndex--, 0);
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

void MapEditor::Render(sf::RenderWindow& window)
{
    if (!activeMap) return;

    activeMap->Render(window);
    DrawGrid(window);
}

void MapEditor::Update(float dt, sf::RenderWindow& window, int selectedTile, int selectedLayer, Camera& camera)
{
    if (!activeMap || activeMap->GetTilesets().empty()) return;

    // Conversion de la position souris en coordonnées map
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(mousePos, camera.GetView());
    sf::Vector2i tilePos(
        static_cast<int>(worldPos.x / activeMap->GetTileSize().x),
        static_cast<int>(worldPos.y / activeMap->GetTileSize().y));

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) &&
        selectedTile >= 0 && tilePos.x >= 0 && tilePos.y >= 0)
    {

        if (selectedLayer < activeMap->GetLayers().size())
        {
            Layer& layer = activeMap->GetLayer(selectedLayer);

            sf::IntRect texRect = activeMap->GetTilesets()[activeTilesetIndex]->GetTileTextureRect(selectedTile);
            Tile newTile(
                sf::Vector2i(tilePos.x * activeMap->GetTileSize().x, tilePos.y * activeMap->GetTileSize().y),
                activeMap->GetTilesets()[activeTilesetIndex]->GetTexture(), texRect, activeTilesetIndex
            );

            layer.SetTile(tilePos.x, tilePos.y, newTile);
        }
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) &&
        selectedTile >= 0 && tilePos.x >= 0 && tilePos.y >= 0)
    {
        Layer& layer = activeMap->GetLayer(selectedLayer);

        Tile newTile(
            sf::Vector2i(0, 0), activeMap->GetTilesets()[activeTilesetIndex]->GetTexture(), {{0, 0}, {0, 0}}, 0
        );

        layer.SetTile(tilePos.x, tilePos.y, newTile);
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
