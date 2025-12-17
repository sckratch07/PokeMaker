#ifndef _CORE_SPRITE_SYSTEM_HPP__
#define _CORE_SPRITE_SYSTEM_HPP__

#include "Core/ECS/Component/ShapeComponent.hpp"
#include "Core/ECS/Component/TransformComponent.hpp"
#include <entt/entt.hpp>

namespace Core
{
    class SpriteSystem
    {
    public:
        void update(entt::registry& reg)
        {
            reg.view<ShapeComponent, TransformComponent>().each([](ShapeComponent& shape, TransformComponent& transform)
            {
                shape.m_shape.setPosition(transform.m_position);
                shape.m_shape.setSize(transform.m_size);
                shape.m_shape.setRotation(sf::degrees(transform.m_rotation));
            });
        }

        void render(entt::registry& reg, sf::RenderWindow& window)
        {
            reg.view<ShapeComponent>().each([&](ShapeComponent& shape)
            {
                window.draw(shape.m_shape);
            });
        }
        
    };
}

#endif