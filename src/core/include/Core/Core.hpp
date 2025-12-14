#ifndef _CORE_CORE_HPP__
#define _CORE_CORE_HPP__

#include <memory>
#include <string>

namespace Core
{
    class StateMachine;
    class Logger;
    class ResourceManager;
    class EntityManager;

    /**
    * @brief Classe centrale du moteur PokeMaker.
    *
    * Cette classe agit comme point d'entrée logique du moteur.
    * Elle initialise et maintient les sous-systèmes fondamentaux :
    * - Machine à états
    * - Gestionnaire d'entités (EnTT)
    * - Gestionnaire de ressources (textures, shaders, etc.)
    * - Système de logging
    *
    * Le module Core ne dépend d'aucune logique de gameplay spécifique.
    * Il peut être utilisé aussi bien par l'éditeur que par le runtime du jeu.
    */
    class CoreEngine
    {
    public:
        /**
        * @brief Constructeur du moteur Core
        *
        * Initialise les sous-systèmes internes mais ne démarre pas
        * la boucle principale.
        */
        CoreEngine();

        /**
        * @brief Destructeur
        *
        * Libère proprement tous les sous-systèmes dans le bon ordre.
        */
        ~CoreEngine();

        /**
        * @brief Initialise explicitement le moteur
        *
        * À appeler une seule fois au démarrage de l'application.
        *
        * @return true si l'initialisation a réussi
        */
        bool initialize();

        /**
        * @brief Met à jour la logique globale du moteur
        * @param dt Delta time en secondes
        */
        void update(float dt);

        /**
        * @brief Accès à la machine à états
        */
        StateMachine& getStateMachine();

        /**
        * @brief Accès au gestionnaire d'entités
        */
        EntityManager& getEntityManager();

        /**
        * @brief Accès au gestionnaire de ressources
        */
        ResourceManager& getResourceManager();

    private:
        std::unique_ptr<StateMachine> m_stateMachine; /**< Gestion des States */
        std::unique_ptr<EntityManager> m_entityManager; /**< EnTT registry wrapper */
        std::unique_ptr<ResourceManager> m_resourceManager; /**< Textures, shaders, etc. */
    };
}

#endif // _CORE_CORE_HPP__