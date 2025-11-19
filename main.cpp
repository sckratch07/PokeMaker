#include <SFML/Graphics.hpp>
#include "Tilemap.hpp"
#include "Tileset.hpp"
#include "AutotileWFC.hpp"
#include "Logger.hpp"
#include <fstream>
#include <optional>
#include <nlohmann/json.hpp>
#include <iostream>

int main() {
    // --- SFML window ---
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(640, 480)), "Tilemap WFC Test");

    // --- Tileset ---
    auto tileset = std::make_shared<Engine::Tileset>();
    if (!tileset->loadFromFile("assets/tilesets/tiles.png", 32, 32)) {
        std::cerr << "Failed to load tileset\n";
        return 1;
    }

    // --- Tilemap ---
    Engine::Tilemap map(10, 10); // 10x10 tiles
    map.setTileset(tileset);
    map.addLayer(Engine::LayerType::Ground);

    // --- Load adjacency rules ---
    Engine::AutotileWFC wfc;
    std::ifstream rulesFile("assets/test.json");
    if (!rulesFile.is_open()) {
        std::cerr << "Cannot open rules.json\n";
        return 1;
    }

    nlohmann::json rulesJson;
    rulesFile >> rulesJson;
    if (!wfc.loadRulesFromJson(rulesJson)) {
        std::cerr << "Failed to load rules\n";
        return 1;
    }

    // --- Apply WFC ---
    if (!wfc.applyWFC(map, Engine::LayerType::Ground, 1234, 10, true)) {
        std::cerr << "WFC failed\n";
        return 1;
    }

    // --- Main loop ---
    sf::Clock clock;
    while (window.isOpen()) {
        while (const std::optional<sf::Event>& event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        float dt = clock.restart().asSeconds();
        map.update(dt);

        window.clear(sf::Color::Black);
        window.draw(map);
        window.display();
    }

    return 0;
}
