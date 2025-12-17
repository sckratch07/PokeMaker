#include "Core/ECS/EntityManager.hpp"
#include "Core/Logger.hpp"

namespace Core
{
    entt::entity EntityManager::createEntity()
    {
        LOG_DEBUG("[EntityManager] : An entity has been created.");
        return m_registry.create();
    }

    void EntityManager::destroyEntity(entt::entity entity)
    {
        if (m_registry.valid(entity))
        {
            m_registry.destroy(entity);
            LOG_DEBUG("[EntityManager] : An entity has been deleted.");
            return;
        }
        LOG_WARN("[EntityManager] : The entity could not be deleted.");
    }

    void EntityManager::clear()
    {
        m_registry.clear();
        LOG_DEBUG("[EntityManager] : The registry has been emptied.");
    }
}