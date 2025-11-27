#ifndef _CORE_RESOURCEMANAGER_HPP__
#define _CORE_RESOURCEMANAGER_HPP__

#include <string>
#include <unordered_map>
#include <memory>
#include <functional>
#include <stdexcept>


namespace Core
{
/**
* @brief Gestionnaire générique de ressources.
*
* Template minimaliste qui stocke des ressources partagées (std::shared_ptr<T>)
* et qui permet d'enregistrer des loaders (fonctions) capables de charger une
* ressource à partir d'un chemin. Le Core n'impose aucun type de ressource
* (texture, audio, etc.) — c'est la responsabilité du code appelant.
*/
template<typename T>
class ResourceManager
{
public:
    using Ptr = std::shared_ptr<T>;
    using Loader = std::function<Ptr(const std::string& path)>;

    ResourceManager() = default;
    ~ResourceManager() = default;

    /**
    * @brief Enregistre un loader qui sera utilisé si une ressource doit être chargée.
    */
    void SetLoader(Loader loader) {
        m_loader = std::move(loader);
    }

    /**
    * @brief Charge (ou récupère depuis le cache) une ressource identifiée par id.
    * @throws std::runtime_error si la ressource n'existe pas et qu'aucun loader n'est défini.
    */
    Ptr Load(const std::string& id, const std::string& path)
    {
        auto it = m_resources.find(id);
        if (it != m_resources.end()) return it->second;
        if (!m_loader) throw std::runtime_error("ResourceManager: pas de loader défini");
        Ptr res = m_loader(path);
        if (!res) throw std::runtime_error("ResourceManager: loader a retourné nullptr pour " + path);
        m_resources.emplace(id, res);
        return res;
    }

    /**
    * @brief Récupère une ressource déjà chargée (ou nullptr si absente).
    */
    Ptr Get(const std::string& id) const noexcept
    {
        auto it = m_resources.find(id);
        if (it == m_resources.end()) return nullptr;
        return it->second;
    }

    /**
    * @brief Supprime la ressource du cache.
    */
    void Unload(const std::string& id)
    {
        m_resources.erase(id);
    }

    /**
    * @brief Vide tout le cache.
    */
    void Clear() noexcept
    {
        m_resources.clear();
    }

private:
    std::unordered_map<std::string, Ptr> m_resources;
    Loader m_loader;
};


} // namespace core

#endif
