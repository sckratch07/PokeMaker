#ifndef _CORE_TRANSFORMCOMPONENT_HPP__
#define _CORE_TRANSFORMCOMPONENT_HPP__

#include <SFML/Graphics.hpp>

namespace Core
{
    struct TransformComponent
    {
		TransformComponent(sf::Vector2f& size, sf::Vector2f& velocity, sf::Vector2f position = {0.f, 0.f}, float rotation = 0.f)
			: m_size(size), m_velocity(velocity), m_position(position), m_rotation(rotation) {}

    	sf::Vector2f m_size;
    	sf::Vector2f m_position;
	    sf::Vector2f m_velocity;
    	float m_rotation;
    };
}

#endif