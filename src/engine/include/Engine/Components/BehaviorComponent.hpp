#ifndef _ENGINE_BEHAVIORCOMPONENT_HPP__
#define _ENGINE_BEHAVIORCOMPONENT_HPP__

/**
 * @file BehaviorComponent.hpp
 * @brief Définition du composant BehaviorComponent.
 *
 * Ce composant contient l'état interne et les paramètres nécessaires
 * au système de comportement (IA simple, comportements scriptés, etc.).
 *
 * Il peut être utilisé pour définir :
 * - l'état actuel du PNJ
 * - une cible à suivre
 * - un timer interne
 * - un comportement générique sous forme d'ID
 */

#include <string>
#include <optional>

namespace Engine
{
    /**
     * @enum BehaviorState
     * @brief États de comportement possibles pour un PNJ ou une entité IA.
     *
     * Ce sont des exemples génériques, modifiables selon les besoins du jeu.
     */
    enum class BehaviorState
    {
        Idle,       ///< L'entité ne fait rien
        Wander,     ///< L'entité se déplace aléatoirement
        Follow,     ///< L'entité suit une cible
        Custom      ///< État personnalisable selon le jeu
    };

    /**
     * @struct BehaviorComponent
     * @brief Composant contenant les informations nécessaires à la gestion du comportement d'une entité.
     */
    struct BehaviorComponent
    {
        BehaviorState state = BehaviorState::Idle; ///< État actuel du comportement

        std::optional<int> targetEntity; ///< Entité ciblée (pour Follow), optionnelle
        float timer = 0.f;               ///< Timer interne utilisé par BehaviorSystem
        int behaviorID = 0;              ///< Identifiant d'un comportement personnalisé
    };
}

#endif
