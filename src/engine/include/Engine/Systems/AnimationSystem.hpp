#ifndef _ENGINE_ANIMATIONSYSTEM_HPP__
#define _ENGINE_ANIMATIONSYSTEM_HPP__

/**
 * @file AnimationSystem.hpp
 * @brief Définition du système AnimationSystem.
 *
 * AnimationSystem met à jour les animations image-par-image des entités
 * possédant un AnimationComponent et un SpriteComponent.
 */

#include "Engine/System.hpp"
#include "Engine/Components/AnimationComponent.hpp"
#include "Engine/Components/SpriteComponent.hpp"

namespace Engine
{
    /**
     * @class AnimationSystem
     * @brief Système gérant la mise à jour des animations.
     *
     * Le système :
     * - incrémente le timer de chaque AnimationComponent
     * - change de frame quand nécessaire
     * - applique la nouvelle frame au SpriteComponent
     */
    class AnimationSystem : public System
    {
    public:
        /**
         * @brief Met à jour toutes les animations valides.
         *
         * @param registry Référence au registry ENTt
         * @param dt Delta time depuis la dernière frame
         */
        void update(entt::registry& registry, float dt) override;
    };
}

#endif
