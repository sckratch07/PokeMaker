#include "Core/ECS/EntityManager.hpp"
#include "Core/Logger.hpp"

namespace Core
{
    void EntityManager::serialize(const json& data)
    {

    }

    entt::entity EntityManager::createEntity()
    {
        entt::entity entity = m_registry.create();
        LOG_DEBUG("[EntityManager] : An entity has been created | ID : {}", static_cast<uint32_t>(entity));
        return entity;
    }

    void EntityManager::addSystem(System* system)
    {
        m_systems.push_back(system);
        LOG_DEBUG("[EntityManager] : The system : {} has been added !", typeid(*system).name());
    }

    void EntityManager::destroyEntity(entt::entity entity)
    {
        if (m_registry.valid(entity))
        {
            LOG_DEBUG("[EntityManager] : An entity has been deleted | ID : {}", static_cast<uint32_t>(entity));
            m_registry.destroy(entity);
            return;
        }
        LOG_WARN("[EntityManager] : The entity could not be deleted.");
    }

    void EntityManager::update(float dt)
    {
        for (auto& system : m_systems)
        {
            system->update(m_registry, dt);
        }
    }

    void EntityManager::render(sf::RenderWindow& window)
    {
        for (auto& system : m_systems)
        {
            system->render(m_registry, window);
        }
    }

    void EntityManager::clearEntities()
    {
        m_registry.clear();
        LOG_DEBUG("[EntityManager] : The registry has been emptied.");
    }

    void EntityManager::clearSystems()
    {
        for (auto system : m_systems)
            delete system;
        
        m_systems.clear();
        LOG_DEBUG("[EntityManager] : All systems has been deleted.");
    }
}