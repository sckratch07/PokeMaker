#include <SFML/Graphics.hpp>
#include "Core/Timer.hpp"
#include "Core/Logger.hpp"
#include "Core/ECS/EntityManager.hpp"
#include "Core/ECS/Component/ShapeComponent.hpp"
#include "Core/ECS/Component/TransformComponent.hpp"
#include "Core/ECS/Component/InputComponent.hpp"
#include "Core/ECS/System/InputSystem.hpp"
#include "Core/ECS/System/SpriteSystem.hpp"

int main()
{
    Core::Logger::Init();
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(1280, 800)), "Test");

    Core::EntityManager entityManager;
    
    entt::registry& reg = entityManager.getRegistry();

    entt::entity joueur = entityManager.createEntity();
    reg.emplace<Core::ShapeComponent>(joueur, 50.f, 50.f);
    reg.emplace<Core::TransformComponent>(joueur, sf::Vector2f(50.f, 50.f), 200.f);
    reg.emplace<Core::InputComponent>(joueur);

    Core::InputSystem intSystem;
    Core::SpriteSystem sprSystem;

    Core::Timer timer;
    float deltatime = 0.f;

    while (window.isOpen())
    {
        while (const std::optional<sf::Event>& event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        timer.reset();
        deltatime = timer.deltaTime();

        intSystem.update(reg, deltatime);
        sprSystem.update(reg);

        window.clear(sf::Color(200, 200, 200));

        sprSystem.render(reg, window);

        window.display();
    }
}