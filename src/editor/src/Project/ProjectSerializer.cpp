#include "Editor/Project/ProjectSerializer.hpp"

#include <fstream>
#include <iostream>

namespace Editor::Project {

// =======================
//     PUBLIC METHODS
// =======================

bool ProjectSerializer::SaveToFile(const std::string& path, const Project& project) const
{
    nlohmann::json j;
    Serialize(j, project);

    std::ofstream file(path);
    if (!file.is_open())
    {
        std::cerr << "[ProjectSerializer] Failed to open file for writing: " << path << std::endl;
        return false;
    }

    file << j.dump(4);
    return true;
}

bool ProjectSerializer::LoadFromFile(const std::string& path, Project& project) const
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cerr << "[ProjectSerializer] Failed to open file: " << path << std::endl;
        return false;
    }

    nlohmann::json j;
    try {
        file >> j;
    }
    catch (const std::exception& e) {
        std::cerr << "[ProjectSerializer] JSON parsing error: " << e.what() << std::endl;
        return false;
    }

    try {
        Deserialize(j, project);
    }
    catch (const std::exception& e) {
        std::cerr << "[ProjectSerializer] JSON structure error: " << e.what() << std::endl;
        return false;
    }

    return true;
}

// =======================
//     SERIALIZATION
// =======================

void ProjectSerializer::Serialize(nlohmann::json& j, const Project& project) const
{
    j["name"]        = project.name;
    j["rootPath"]    = project.rootPath;
    j["description"] = project.description;
    j["tileSize"]    = project.tileSize;

    // tilesets
    j["tilesets"] = nlohmann::json::array();
    for (auto const& ts : project.tilesets)
        j["tilesets"].push_back(ToJson(ts));

    // maps
    j["maps"] = nlohmann::json::array();
    for (auto const& map : project.maps)
        j["maps"].push_back(ToJson(map));

    // npcs
    j["npcs"] = nlohmann::json::array();
    for (auto const& npc : project.npcs)
        j["npcs"].push_back(ToJson(npc));

    // shaders
    j["shaders"] = nlohmann::json::array();
    for (auto const& s : project.shaders)
        j["shaders"].push_back(ToJson(s));
}

void ProjectSerializer::Deserialize(const nlohmann::json& j, Project& project) const
{
    project.name        = j.value("name", "NewProject");
    project.rootPath    = j.value("rootPath", ".");
    project.description = j.value("description", "");
    project.tileSize    = j.value("tileSize", 16);

    // --- tilesets ---
    project.tilesets.clear();
    if (j.contains("tilesets"))
    {
        for (auto const& ts : j["tilesets"])
            project.tilesets.push_back(FromJsonTileSet(ts));
    }

    // --- maps ---
    project.maps.clear();
    if (j.contains("maps"))
    {
        for (auto const& m : j["maps"])
            project.maps.push_back(FromJsonMap(m));
    }

    // --- npcs ---
    project.npcs.clear();
    if (j.contains("npcs"))
    {
        for (auto const& n : j["npcs"])
            project.npcs.push_back(FromJsonNPC(n));
    }

    // --- shaders ---
    project.shaders.clear();
    if (j.contains("shaders"))
    {
        for (auto const& s : j["shaders"])
            project.shaders.push_back(FromJsonShader(s));
    }

    // Le timestamp runtime n'est jamais stocké — on le remet à maintenant
    project.lastModified = std::chrono::system_clock::now();
}

// =======================
//  SUB-SERIALIZERS
// =======================

// -------- TileSetDescriptor --------
nlohmann::json ProjectSerializer::ToJson(const TileSetDescriptor& ts)
{
    nlohmann::json j;
    j["name"]         = ts.name;
    j["relativePath"] = ts.relativePath;
    j["tileWidth"]    = ts.tileWidth;
    j["tileHeight"]   = ts.tileHeight;
    j["margin"]       = ts.margin;
    j["spacing"]      = ts.spacing;
    return j;
}

TileSetDescriptor ProjectSerializer::FromJsonTileSet(const nlohmann::json& j)
{
    TileSetDescriptor ts;
    ts.name         = j.value("name", "");
    ts.relativePath = j.value("relativePath", "");
    ts.tileWidth    = j.value("tileWidth", 16);
    ts.tileHeight   = j.value("tileHeight", 16);
    ts.margin       = j.value("margin", 0);
    ts.spacing      = j.value("spacing", 0);
    return ts;
}

// -------- LayerDescriptor --------
nlohmann::json ProjectSerializer::ToJson(const LayerDescriptor& layer)
{
    nlohmann::json j;
    j["name"]    = layer.name;
    j["visible"] = layer.visible;
    j["opacity"] = layer.opacity;
    j["zIndex"]  = layer.zIndex;
    return j;
}

LayerDescriptor ProjectSerializer::FromJsonLayer(const nlohmann::json& j)
{
    LayerDescriptor l;
    l.name    = j.value("name", "Layer");
    l.visible = j.value("visible", true);
    l.opacity = j.value("opacity", 1.0f);
    l.zIndex  = j.value("zIndex", 0);
    return l;
}

// -------- MapDescriptor --------
nlohmann::json ProjectSerializer::ToJson(const MapDescriptor& map)
{
    nlohmann::json j;
    j["name"]         = map.name;
    j["relativePath"] = map.relativePath;
    j["width"]        = map.width;
    j["height"]       = map.height;
    j["tileSize"]     = map.tileSize;

    j["layers"] = nlohmann::json::array();
    for (auto const& l : map.layers)
        j["layers"].push_back(ToJson(l));

    j["usedTileSets"] = map.usedTileSets;

    return j;
}

MapDescriptor ProjectSerializer::FromJsonMap(const nlohmann::json& j)
{
    MapDescriptor m;
    m.name         = j.value("name", "Map");
    m.relativePath = j.value("relativePath", "");
    m.width        = j.value("width", 100);
    m.height       = j.value("height", 100);
    m.tileSize     = j.value("tileSize", 16);

    // layers
    if (j.contains("layers"))
    {
        for (auto const& l : j["layers"])
            m.layers.push_back(FromJsonLayer(l));
    }

    m.usedTileSets = j.value("usedTileSets", std::vector<std::string>{});
    m.loaded = false;

    return m;
}

// -------- NPCDescriptor --------
nlohmann::json ProjectSerializer::ToJson(const NPCDescriptor& npc)
{
    nlohmann::json j;
    j["id"]           = npc.id;
    j["relativePath"] = npc.relativePath;
    j["displayName"]  = npc.displayName;
    j["type"]         = npc.type;
    j["meta"]         = npc.meta;
    return j;
}

NPCDescriptor ProjectSerializer::FromJsonNPC(const nlohmann::json& j)
{
    NPCDescriptor n;
    n.id           = j.value("id", "");
    n.relativePath = j.value("relativePath", "");
    n.displayName  = j.value("displayName", "");
    n.type         = j.value("type", "");
    if (j.contains("meta")) n.meta = j["meta"].get<std::unordered_map<std::string, std::string>>();
    return n;
}

// -------- ShaderDescriptor --------
nlohmann::json ProjectSerializer::ToJson(const ShaderDescriptor& shader)
{
    nlohmann::json j;
    j["name"]         = shader.name;
    j["relativePath"] = shader.relativePath;
    j["uniforms"]     = shader.uniforms;
    return j;
}

ShaderDescriptor ProjectSerializer::FromJsonShader(const nlohmann::json& j)
{
    ShaderDescriptor s;
    s.name         = j.value("name", "");
    s.relativePath = j.value("relativePath", "");

    if (j.contains("uniforms"))
        s.uniforms = j["uniforms"].get<std::unordered_map<std::string, std::string>>();

    return s;
}

} // namespace Editor::Project
