#ifndef _CORE_SHAPE_COMPONENT_HPP__
#define _CORE_SHAPE_COMPONENT_HPP__

#include <SFML/Graphics.hpp>

namespace Core
{
    struct ShapeComponent
    {
        ShapeComponent(float width, float height) : m_shape({width, height}) {}
    	sf::RectangleShape m_shape;
    };
}

#endif