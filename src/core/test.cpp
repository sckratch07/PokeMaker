#include <SFML/Graphics.hpp>
#include "Core/Timer.hpp"
#include "Core/ECS/EntityManager.hpp"
#include "Core/ECS/Component/ShapeComponent.hpp"
#include "Core/ECS/Component/TransformComponent.hpp"
#include "Core/ECS/Component/InputComponent.hpp"
#include "Core/ECS/System/InputSystem.hpp"
#include "Core/ECS/System/SpriteSystem.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(1280, 800)), "Test");

    Core::EntityManager entityManager;
    
    entt::registry& reg = entityManager.getRegistry();

    entt::entity joueur = entityManager.createEntity();
    reg.emplace<Core::ShapeComponent>(joueur);
    reg.emplace<Core::TransformComponent>(joueur, sf::Vector2f(50.f, 50.f), sf::Vector2f(200.f, 200.f));
    reg.emplace<Core::InputComponent>(joueur);

    Core::InputSystem intSystem;
    Core::SpriteSystem sprSystem;

    while (window.isOpen())
    {
        while (const std::optional<sf::Event>& event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        intSystem.update(reg, );


    }
}