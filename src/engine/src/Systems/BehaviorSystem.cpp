#include "Engine/Systems/BehaviorSystem.hpp"
#include <cmath>
#include <cstdlib>

/**
 * @file BehaviorSystem.cpp
 * @brief Implémentation du système BehaviorSystem.
 */

namespace Engine
{
    void BehaviorSystem::update(entt::registry& registry, float dt)
    {
        auto view = registry.view<BehaviorComponent, TransformComponent>();

        view.each([&](entt::entity entity, BehaviorComponent& behavior, TransformComponent& transform)
        {
            behavior.timer += dt; // Timer interne

            switch (behavior.state)
            {
                case BehaviorState::Idle:
                    // Rien à faire
                    break;

                case BehaviorState::Wander:
                    applyWander(transform, behavior, dt);
                    break;

                case BehaviorState::Follow:
                    applyFollow(registry, transform, behavior, dt);
                    break;

                case BehaviorState::Custom:
                    // Cette partie pourra être étendue selon les besoins du jeu
                    // Le behaviorID peut être utilisé pour du script ou autre logique
                    break;
            }
        });
    }

    void BehaviorSystem::applyWander(TransformComponent& transform, BehaviorComponent& behavior, float dt)
    {
        // Change parfois de direction aléatoirement
        if (behavior.timer >= 1.f)
        {
            behavior.timer = 0.f;

            // Petit déplacement aléatoire entre -1 et 1
            float dx = (std::rand() % 200 - 100) / 100.f;
            float dy = (std::rand() % 200 - 100) / 100.f;

            transform.position.x += dx * 20.f * dt; // vitesse 20
            transform.position.y += dy * 20.f * dt;
        }
    }

    void BehaviorSystem::applyFollow(entt::registry& registry, TransformComponent& transform, BehaviorComponent& behavior, float dt)
    {
        if (!behavior.targetEntity.has_value())
            return;

        entt::entity target = (entt::entity)behavior.targetEntity.value();

        if (!registry.valid(target))
            return;

        auto targetTransform = registry.try_get<TransformComponent>(target);
        if (!targetTransform)
            return;

        // Direction vers la cible
        sf::Vector2f dir{
            targetTransform->position.x - transform.position.x,
            targetTransform->position.y - transform.position.y
        };

        float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        if (length == 0.f)
            return;

        // Normalisation
        dir.x /= length;
        dir.y /= length;

        // Déplacement vers la cible (vitesse 30)
        transform.position.x += dir.x * 30.f * dt;
        transform.position.y += dir.y * 30.f * dt;
    }
}
