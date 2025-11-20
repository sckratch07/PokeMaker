#ifndef _ENGINE_NPCCOMPONENT_HPP__
#define _ENGINE_NPCCOMPONENT_HPP__

/**
 * @file NPCComponent.hpp
 * @brief Définition du composant NPCComponent.
 *
 * Ce composant identifie une entité comme un PNJ (Personnage Non Joueur).
 * Il peut contenir des informations spécifiques telles que :
 * - le nom du PNJ
 * - un identifiant ou type (marchand, dresseur, etc.)
 * - un flag indiquant si le PNJ peut interagir avec le joueur
 *
 * Le comportement réel est géré par BehaviorComponent et BehaviorSystem.
 */

#include <string>

namespace Engine
{
    /**
     * @struct NPCComponent
     * @brief Composant décrivant un personnage non joueur.
     *
     * Ce composant contient des informations simples, utiles pour
     * la logique de dialogue, d'interaction ou d'IA.
     */
    struct NPCComponent
    {
        std::string name = "NPC";  ///< Nom affiché ou identifiant du PNJ
        int npcType = 0;           ///< Type ou catégorie de PNJ (0 = normal, autres = spécifiques)
        bool canInteract = true;   ///< Indique si le joueur peut interagir avec ce PNJ
    };
}

#endif
