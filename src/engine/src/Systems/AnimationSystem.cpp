#include "Engine/Systems/AnimationSystem.hpp"

/**
 * @file AnimationSystem.cpp
 * @brief Implémentation du système AnimationSystem.
 */

namespace Engine
{
    void AnimationSystem::update(entt::registry& registry, float dt)
    {
        // Vue ENTt : toutes les entités possédant AnimationComponent + SpriteComponent
        auto view = registry.view<AnimationComponent, SpriteComponent>();

        view.each([&](entt::entity entity, AnimationComponent& anim, SpriteComponent& sprite)
        {
            // Vérifie si l'animation a des frames
            if (!anim.isValid())
                return;

            // Incrémentation du timer
            anim.timer += dt;

            // Si on dépasse la durée d'une frame, on passe à la suivante
            if (anim.timer >= anim.frameTime)
            {
                anim.timer -= anim.frameTime; // Reset (mais conserve le surplus)
                anim.currentFrame++;

                // Gestion de la boucle
                if (anim.currentFrame >= anim.frames.size())
                {
                    if (anim.loop)
                        anim.currentFrame = 0;
                    else
                        anim.currentFrame = anim.frames.size() - 1; // On reste sur la dernière frame
                }

                // Applique la nouvelle frame au sprite
                sprite.sprite.setTextureRect(anim.frames[anim.currentFrame]);
            }
        });
    }
}
