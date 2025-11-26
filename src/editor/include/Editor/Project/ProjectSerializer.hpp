#ifndef _EDITOR_PROJECTSERIALIZER_HPP__
#define _EDITOR_PROJECTSERIALIZER_HPP__

/**
 * @file ProjectSerializer.hpp
 * @brief Sérialisation JSON complète d'un projet (version avancée).
 */

#include <string>
#include <nlohmann/json.hpp>

#include "Editor/Project/Project.hpp"

namespace Editor::Project {

class ProjectSerializer
{
public:
    ProjectSerializer() = default;
    ~ProjectSerializer() = default;

    bool SaveToFile(const std::string& path, const Project& project) const;
    bool LoadFromFile(const std::string& path, Project& project) const;

private:
    void Serialize(nlohmann::json& j, const Project& project) const;
    void Deserialize(const nlohmann::json& j, Project& project) const;

    // sous-sérialisation
    static nlohmann::json ToJson(const TileSetDescriptor& ts);
    static nlohmann::json ToJson(const MapDescriptor& map);
    static nlohmann::json ToJson(const LayerDescriptor& layer);
    static nlohmann::json ToJson(const NPCDescriptor& npc);
    static nlohmann::json ToJson(const ShaderDescriptor& shader);

    static TileSetDescriptor FromJsonTileSet(const nlohmann::json& j);
    static MapDescriptor FromJsonMap(const nlohmann::json& j);
    static LayerDescriptor FromJsonLayer(const nlohmann::json& j);
    static NPCDescriptor FromJsonNPC(const nlohmann::json& j);
    static ShaderDescriptor FromJsonShader(const nlohmann::json& j);
};

} // namespace Editor::Project

#endif // _EDITOR_PROJECTSERIALIZER_HPP__
