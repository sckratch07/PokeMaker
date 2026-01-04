#ifndef _CORE_SYSTEM_HPP__
#define _CORE_SYSTEM_HPP__

#include "Core/ECS/Component/Components.hpp"
#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>

namespace Core
{
    class System
    {
        public:
            virtual void update(entt::registry& reg, float dt) {}
            virtual void render(entt::registry& reg, sf::RenderWindow& window) {}
    };
}

#endif
