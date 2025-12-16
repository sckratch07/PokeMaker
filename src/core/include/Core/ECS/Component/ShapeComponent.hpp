#ifndef _CORE_SHAPECOMPONENT_HPP__
#define _CORE_SHAPECOMPONENT_HPP__

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