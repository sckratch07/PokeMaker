#ifndef _ENGINE_WORLD_HPP__
#define _ENGINE_WORLD_HPP__

/**
 * @file World.hpp
 * @brief Définition de la classe World, cœur du moteur ECS.
 *
 * La classe World encapsule un registry EnTT et gère :
 * - la création/destruction d'entités
 * - l'ajout et la gestion des systèmes
 * - la mise à jour globale du moteur via update()
 *
 * Elle agit comme environnement principal dans lequel vivent les entités
 * et les systèmes du jeu.
 */

#include <entt/entt.hpp>
#include <memory>
#include <vector>

#include "Engine/System.hpp"

namespace Engine
{
    /**
     * @class World
     * @brief Classe représentant l’environnement ECS global.
     *
     * World fournit une interface simple pour gérer les entités,
     * stocker le registry EnTT et exécuter les différents systèmes.
     */
    class World
    {
    public:
        /**
         * @brief Constructeur par défaut.
         */
        World();

        /**
         * @brief Destructeur par défaut.
         */
        ~World() = default;

        /**
         * @brief Crée une nouvelle entité dans le monde.
         * @return Un handle vers la nouvelle entité.
         */
        entt::entity createEntity();

        /**
         * @brief Détruit une entité existante.
         * @param entity L'entité à détruire.
         */
        void destroyEntity(entt::entity entity);

        /**
         * @brief Ajoute un système au monde.
         *
         * Le système est stocké et sera mis à jour à chaque update().
         *
         * @param system Un pointeur unique vers un système dérivé de System.
         */
        void addSystem(std::unique_ptr<System> system);

        /**
         * @brief Met à jour tous les systèmes du monde.
         *
         * @param dt Delta time en secondes.
         */
        void update(float dt);

        /**
         * @brief Accès au registre ENTt.
         * @return Référence vers le registry interne.
         */
        entt::registry& getRegistry();

    private:
        entt::registry m_registry;                   ///< Registry ENTt stockant entités et composants
        std::vector<std::unique_ptr<System>> m_systems; ///< Liste des systèmes actifs
    };
}

#endif
