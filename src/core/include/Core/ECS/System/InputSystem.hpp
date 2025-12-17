#ifndef _CORE_INPUT_SYSTEM_HPP__
#define _CORE_INPUT_SYSTEM_HPP__

#include "Core/ECS/Component/TransformComponent.hpp"
#include "Core/ECS/Component/InputComponent.hpp"
#include <entt/entt.hpp>

namespace Core
{
    class InputSystem
    {
    public:
        void update(entt::registry& reg, float dt)
        {
            reg.view<TransformComponent, InputComponent>().each([&](TransformComponent& transform, InputComponent& input)
            {
                input.updateKey();

                sf::Vector2f dir(0.f, 0.f);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W))
                    dir.y = -1;
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S))
                    dir.y = 1;
                
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
                    dir.x = -1;
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D))
                    dir.x = 1;
                
                if (dir.x != 0.f || dir.y != 0)
                {
                    dir = dir.normalized() * transform.m_velocity * dt;
                    transform.m_position += dir;
                }
            });
        }
    };
}

#endif