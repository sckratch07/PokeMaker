#ifndef _CORE_APPLICATION_HPP__
#define _CORE_APPLICATION_HPP__

#include <SFML/Graphics.hpp>

namespace Application
{
    class EntityManager;

    class Application
    {
    public:
        Application(
            std::string name = "PokeMaker",
            sf::Vector2u size = { 1584, 864 }
        ) : m_name(name), m_size(size), m_window(sf::VideoMode(size), name) {}

        virtual ~Application() = default;

        virtual void run();

        const std::string& getName() const { return m_name; }
        const sf::Vector2u& getSize() const { return m_size; }

    private:
        virtual void handleEvents(const std::optional<sf::Event>& event);
        virtual void render();

        sf::RenderWindow m_window;
        std::string m_name;
        sf::Vector2u m_size;

        std::unique_ptr<EntityManager> m_entityManager;
    };
}

#endif