#include "Engine/Systems/PhysicsSystem.hpp"

/**
 * @file PhysicsSystem.cpp
 * @brief Implémentation du système PhysicsSystem.
 */

namespace Engine
{
    bool PhysicsSystem::intersects(const sf::FloatRect& a, const sf::FloatRect& b) const
    {
        return (a.contains(b.position) || a.contains({b.position.x + b.size.x, b.position.y}) ||
            a.contains(b.position + b.size) || a.contains({b.position.x, b.position.y + b.size.y}));
    }

    void PhysicsSystem::update(entt::registry& registry, float dt)
    {
        auto view = registry.view<TransformComponent, CollisionComponent>();
    
        view.each([&](entt::entity entityA, TransformComponent& transformA, CollisionComponent& collisionA)
        {
            sf::FloatRect boundsA = collisionA.bounds;
            boundsA.position.x += transformA.position.x;
            boundsA.position.y += transformA.position.y;

            view.each([&](entt::entity entityB, TransformComponent& transformB, CollisionComponent& collisionB)
            {
                if (entityA == entityB)
                    return;

                if (!collisionA.isSolid || !collisionB.isSolid)
                    return;

                sf::FloatRect boundsB = collisionB.bounds;
                boundsB.position.x += transformB.position.x;
                boundsB.position.y += transformB.position.y;

                if (intersects(boundsA, boundsB))
                {
                    float overlapLeft   = (boundsA.position.x + boundsA.size.x) - boundsB.position.x;
                    float overlapRight  = (boundsB.position.x + boundsB.size.x) - boundsA.position.x;
                    float overlapTop    = (boundsA.position.y + boundsA.size.y) - boundsB.position.y;
                    float overlapBottom = (boundsB.position.y + boundsB.size.y) - boundsA.position.y;

                    float smallest = std::min({ overlapLeft, overlapRight, overlapTop, overlapBottom });

                    if (smallest == overlapLeft)
                        transformA.position.x -= overlapLeft;
                    else if (smallest == overlapRight)
                        transformA.position.x += overlapRight;
                    else if (smallest == overlapTop)
                        transformA.position.y -= overlapTop;
                    else if (smallest == overlapBottom)
                        transformA.position.y += overlapBottom;
                }
            });
        });
    }
}
