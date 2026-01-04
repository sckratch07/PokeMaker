#ifndef _CORE_SPRITE_SYSTEM_HPP__
#define _CORE_SPRITE_SYSTEM_HPP__

#include <Core/ECS/System/System.hpp>

namespace Core
{
    class SpriteSystem : public System
    {
    public:
        void update(entt::registry& reg)
        {
            reg.view<ShapeComponent, TransformComponent>().each([](entt::entity, ShapeComponent& shape, TransformComponent& transform)
            {
                shape.m_shape.setPosition(transform.m_position);
                shape.m_shape.setSize(transform.m_size);
                shape.m_shape.setRotation(sf::degrees(transform.m_rotation));
            });
        }

        void render(entt::registry& reg, sf::RenderWindow& window)
        {
            reg.view<ShapeComponent>().each([&](entt::entity, ShapeComponent& shape)
            {
                window.draw(shape.m_shape);
            });
        }
        
    };
}

#endif