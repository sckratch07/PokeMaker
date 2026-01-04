#ifndef _CORE_APPLICATION_HPP__
#define _CORE_APPLICATION_HPP__

#include "Core/ProjectManager.hpp"
#include "Core/ECS/EntityManager.hpp"
#include "Core/Timer.hpp"
#include <SFML/Graphics.hpp>

namespace Core
{
    class Application
    {
    public:
        Application(const std::string name = "PokeMaker", sf::Vector2u size = { 1584, 864 })
            : m_name(name), m_size(size)
        {
            m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(size), name);

            m_projectManager = std::make_unique<Core::ProjectManager>();
            m_entityManager = std::make_unique<Core::EntityManager>();
            m_timer = std::make_unique<Core::Timer>();
        }

        virtual ~Application() = default;

        void run()
        {
            init();
            while (m_window->isOpen())
            {
                m_timer->tick();

                while (std::optional<sf::Event> event = m_window->pollEvent())
                {
                    handleEvents(event);
                }

                update();

                m_window->clear(sf::Color(20, 23, 30));
                
                render();

                m_window->display();
            }
        }

        const std::string& getName() const { return m_name; }
        const sf::Vector2u& getSize() const { return m_size; }

    protected:
        virtual void init() = 0;
        virtual void handleEvents(const std::optional<sf::Event>& event) = 0;
        virtual void update() = 0;
        virtual void render() = 0;

        std::shared_ptr<sf::RenderWindow> m_window;
        std::string m_name;
        sf::Vector2u m_size;

        std::shared_ptr<ProjectManager> m_projectManager;
        std::shared_ptr<EntityManager> m_entityManager;
        std::shared_ptr<Timer> m_timer;
    };
}

#endif