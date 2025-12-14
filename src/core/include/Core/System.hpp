#ifndef _CORE_SYSTEM_HPP__
#define _CORE_SYSTEM_HPP__

#include <SFML/Graphics.hpp>

namespace Core
{
    class EntityManager;

    /**
    * @brief Classe de base pour tous les systèmes ECS.
    *
    * Un System contient de la logique opérant sur un ensemble
    * d'entités possédant certains composants.
    *
    * Les systèmes sont :
    * - sans état (ou état minimal)
    * - exécutés depuis les States
    * - découplés des entités elles-mêmes
    */
    class System
    {
    public:
        virtual ~System() = default;


        /**
        * @brief Mise à jour logique du système
        * @param entityManager Gestionnaire d'entités
        * @param dt Delta time en secondes
        */
        virtual void update(EntityManager& entityManager, float dt) = 0;


        /**
        * @brief Rendu du système (optionnel)
        * @param entityManager Gestionnaire d'entités
        * @param window Fenêtre SFML
        */
        virtual void render(EntityManager& entityManager, sf::RenderWindow& window) {}
    };
}

#endif // _CORE_SYSTEM_HPP__