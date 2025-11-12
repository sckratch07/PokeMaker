#include "SFML/Graphics.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(1280, 720)), "PokeMaker");

    while (window.isOpen())
    {
        while (const std::optional<sf::Event>& event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::Blue);
        // Rendering code goes here
        window.display();
    }

    return 0;
}