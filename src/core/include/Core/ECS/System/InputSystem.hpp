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
            reg.view<TransformComponent, InputComponent>().each([&](auto entity, TransformComponent& transform, InputComponent& input)
            {
                input.updateKey();

                sf::Vector2f dir(0.f, 0.f);
                if (input.m_keys[sf::Keyboard::Scancode::W])
                    dir.y = -1;
                else if (input.m_keys[sf::Keyboard::Scancode::S])
                    dir.y = 1;
                
                if (input.m_keys[sf::Keyboard::Scancode::A])
                    dir.x = -1;
                else if (input.m_keys[sf::Keyboard::Scancode::D])
                    dir.x = 1;
                
                if (dir.x != 0.f || dir.y != 0)
                {
                    dir = transform.m_velocity * dir.normalized() * dt;
                    transform.m_position += dir;
                }
            });
        }
    };
}

#endif