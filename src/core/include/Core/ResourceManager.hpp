#ifndef _CORE_RESOURCEMANAGER_HPP__
#define _CORE_RESOURCEMANAGER_HPP__

#include <string>
#include <memory>
#include <unordered_map>
#include <shared_mutex>
#include <functional>

namespace Core
{
/**
 * @brief Interface de base pour les ressources gérées.
 *
 * Les ressources réelles (ex: textures, sons) peuvent hériter de Resource.
 * Le ResourceManager conserve des shared_ptr<Resource>.
 */
struct Resource
{
    virtual ~Resource() = default;
};

/**
 * @brief Gestionnaire simple de ressources (thread-safe).
 *
 * Le ResourceManager conserve des ressources identifiées par leur chemin/clé.
 * Le chargement se fait via une lambda fournie par l'appelant, qui renvoie
 * un std::shared_ptr<T> où T dérive de Core::Resource.
 *
 * Méthode typique :
 * @code
 * auto tex = resourceManager.load<Texture>("tiles.png", [](const std::string& p){
 *     return std::make_shared<Texture>(loadFromFile(p));
 * });
 * @endcode
 */
class ResourceManager
{
public:
    ResourceManager() = default;
    ~ResourceManager() = default;

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    /**
     * @brief Charge (ou retourne en cache) une ressource du type T.
     *
     * @tparam T Type de la ressource (doit dériver de Core::Resource).
     * @param key Clé / chemin unique identifiant la ressource.
     * @param loader Fonction qui charge la ressource si elle n'existe pas.
     *               Signature : std::shared_ptr<T> (const std::string& key)
     * @return std::shared_ptr<T> pointeur partagé vers la ressource.
     */
    template<typename T>
    std::shared_ptr<T> load(const std::string& key, std::function<std::shared_ptr<T>(const std::string&)> loader);

    /**
     * @brief Récupère une ressource existante (null si absente).
     */
    template<typename T>
    std::shared_ptr<T> get(const std::string& key);

    /**
     * @brief Décharge (supprime) la ressource référencée par key.
     */
    void unload(const std::string& key);

    /**
     * @brief Vide toutes les ressources.
     */
    void clear();

private:
    std::unordered_map<std::string, std::shared_ptr<Resource>> m_resources;
    mutable std::shared_mutex m_mutex;
};

// Definitions des templates (inline)

template<typename T>
std::shared_ptr<T> ResourceManager::load(const std::string& key, std::function<std::shared_ptr<T>(const std::string&)> loader)
{
    static_assert(std::is_base_of<Resource, T>::value, "T doit dériver de Core::Resource");

    {
        std::shared_lock lock(m_mutex);
        auto it = m_resources.find(key);
        if (it != m_resources.end()) {
            return std::static_pointer_cast<T>(it->second);
        }
    }

    // Charger sans verrou partagé
    auto resource = loader(key);
    if (!resource)
    {
        return nullptr;
    }

    {
        std::unique_lock lock(m_mutex);
        m_resources[key] = std::static_pointer_cast<Resource>(resource);
    }

    return resource;
}

template<typename T>
std::shared_ptr<T> ResourceManager::get(const std::string& key)
{
    static_assert(std::is_base_of<Resource, T>::value, "T doit dériver de Core::Resource");

    std::shared_lock lock(m_mutex);
    auto it = m_resources.find(key);
    if (it == m_resources.end()) { return nullptr; }
    return std::static_pointer_cast<T>(it->second);
}

} // namespace Core

#endif
