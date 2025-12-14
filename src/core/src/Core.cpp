#include "Core/Core.hpp"

// Forward includes (évite les dépendances circulaires)
#include "Core/StateMachine.hpp"
#include "Core/EntityManager.hpp"
#include "Core/ResourceManager.hpp"

namespace Core
{
    CoreEngine::CoreEngine()
    : m_stateMachine(nullptr)
    , m_entityManager(nullptr)
    , m_resourceManager(nullptr)
    {
    }

    CoreEngine::~CoreEngine()
    {
        m_stateMachine.reset();
        m_entityManager.reset();
        m_resourceManager.reset();
    }

    bool CoreEngine::initialize()
    {
        // Création des sous-systèmes fondamentaux
        m_stateMachine = std::make_unique<StateMachine>();
        m_entityManager = std::make_unique<EntityManager>();
        m_resourceManager = std::make_unique<ResourceManager>();

        // Ici pourront être ajoutées :
        // - Initialisation du logger
        // - Chargement des ressources globales
        // - Configuration initiale

        return true;
    }

    void CoreEngine::update(float dt)
    {
        // Mise à jour de l'état actif
        if (m_stateMachine)
            m_stateMachine->update(dt);
    }

    StateMachine& CoreEngine::getStateMachine()
    {
        return *m_stateMachine;
    }

    EntityManager& CoreEngine::getEntityManager()
    {
        return *m_entityManager;
    }

    ResourceManager& CoreEngine::getResourceManager()
    {
        return *m_resourceManager;
    }
}