#ifndef _CORE_COMPONENT_HPP__
#define _CORE_COMPONENT_HPP__

#include <SFML/Graphics.hpp>
#include <string>

namespace Core
{
    /**
    * @brief Composant de transformation spatiale.
    *
    * Utilisé par toutes les entités positionnées dans le monde :
    * - Joueur
    * - NPC
    * - Objets
    * - Entités de map (tiles dynamiques)
    */
    struct TransformComponent
    {
        sf::Vector2f position {0.f, 0.f}; /**< Position monde */
        sf::Vector2f scale {1.f, 1.f}; /**< Échelle */
        float rotation = 0.f; /**< Rotation en degrés */
    };


    /**
    * @brief Composant graphique basé sur SFML.
    *
    * Sépare la notion de ressource (texture) du rendu.
    */
    struct SpriteComponent
    {
        sf::Sprite sprite; /**< Sprite SFML */
        bool visible = true; /**< Permet de masquer l'entité */
    };


    /**
    * @brief Composant identitaire.
    *
    * Permet de nommer les entités pour :
    * - l'éditeur
    * - le debug
    * - la sérialisation
    */
    struct NameComponent
    {
        std::string name;
    };


    /**
    * @brief Composant de collision simple (AABB).
    */
    struct CollisionComponent
    {
        sf::FloatRect bounds; /**< Boîte de collision */
        bool isTrigger = false; /**< Collision ou trigger */
    };


    /**
    * @brief Composant de comportement logique.
    *
    * Sert de base pour :
    * - IA des NPC
    * - Scripts joueur
    * - Interactions
    */
    struct BehaviorComponent
    {
        std::string behaviorId; /**< Identifiant du comportement */
    };
}

#endif // _CORE_COMPONENT_HPP__