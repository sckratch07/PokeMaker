#include <Core.hpp>
#include <Engine.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <nlohmann/json.hpp>
#include <fstream>

void runWFCOnTilemap(Engine::Tilemap& map)
{
    // Chemin vers le fichier JSON
    const std::string ruleFile = "assets/test.json";

    // Charger fichier JSON depuis disque
    std::ifstream f(ruleFile);
    if (!f.is_open()) {
        Core::log("Impossible d'ouvrir le fichier de règles : " + ruleFile, Core::LogLevel::Error);
        return;
    }

    json j;
    try {
        f >> j;
    } catch (std::exception& e) {
        Core::log(std::string("Erreur JSON : ") + e.what(), Core::LogLevel::Error);
        return;
    }

    // Préparer WFC
    Engine::AutotileWFC wfc;
    if (!wfc.loadRulesFromJson(j)) {
        Core::log("Impossible de charger les règles depuis le JSON.", Core::LogLevel::Error);
        return;
    }

    wfc.setSeed(123456);

    // Appliquer WFC sur un layer
    bool ok = wfc.applyWFC(map, Engine::LayerType::Ground, 123456, 10, true);

    if (!ok) {
        Core::log("WFC a échoué : aucune solution trouvée.", Core::LogLevel::Error);
        return;
    }

    Core::log("WFC appliqué avec succès sur la tilemap !", Core::LogLevel::Info);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 600)), "PokeMaker");
    window.setFramerateLimit(60);

    if (ImGui::SFML::Init(window))
        ImGuiIO& io = ImGui::GetIO();

    sf::Clock timer;
    sf::Time dt;

    Engine::Tilemap map(800, 600);
    std::shared_ptr<Engine::Tileset> tileset = std::make_shared<Engine::Tileset>();
    tileset->loadFromFile("assets/tilesets/grass.png", 32, 32);
    map.setTileset(tileset);

    while (window.isOpen())
    {
        dt = timer.restart();

        while (const std::optional<sf::Event>& event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        ImGui::SFML::Update(window, dt);

        if (ImGui::Begin("Tools"))
        {
            if (ImGui::Button("Générer WFC sur Ground"))
            {
                runWFCOnTilemap(map);
            }
        }
        ImGui::End();

        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
}
