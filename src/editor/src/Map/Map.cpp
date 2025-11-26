#include "Editor/Map/Map.hpp"

#include <fstream>
#include <iostream>
#include <filesystem>

namespace Editor::Map {

using json = nlohmann::json;
namespace fs = std::filesystem;

Map::Map(const Project::MapDescriptor& desc)
    : m_descriptor(desc)
{
    RebuildTileMapFromDescriptor();
}

const Project::MapDescriptor& Map::GetDescriptor() const { return m_descriptor; }
Project::MapDescriptor& Map::GetDescriptor() { return m_descriptor; }

TileMap& Map::GetTileMap() { return m_tileMap; }
const TileMap& Map::GetTileMap() const { return m_tileMap; }

void Map::RebuildTileMapFromDescriptor()
{
    m_tileMap.Clear();
    m_tileMap = TileMap(m_descriptor.width, m_descriptor.height, m_descriptor.tileSize);
    // create layers from descriptor
    for (auto const& ld : m_descriptor.layers)
    {
        Layer& l = m_tileMap.AddLayer(ld.name);
        (void)l;
    }
}

bool Map::LoadFromFile(const std::string& rootPath)
{
    if (m_descriptor.relativePath.empty()) {
        std::cerr << "[Map] No relativePath set for map '" << m_descriptor.name << "'\n";
        return false;
    }
    fs::path path = fs::path(rootPath) / m_descriptor.relativePath;
    if (!fs::exists(path)) {
        std::cerr << "[Map] Map file does not exist: " << path.string() << "\n";
        return false;
    }

    std::ifstream ifs(path);
    if (!ifs.is_open()) return false;

    json j;
    try {
        ifs >> j;
    } catch (const std::exception& e) {
        std::cerr << "[Map] JSON parse error: " << e.what() << "\n";
        return false;
    }

    // Read basic descriptor fields if present
    m_descriptor.name = j.value("name", m_descriptor.name);
    m_descriptor.width = j.value("width", m_descriptor.width);
    m_descriptor.height = j.value("height", m_descriptor.height);
    m_descriptor.tileSize = j.value("tileSize", m_descriptor.tileSize);

    if (j.contains("layers")) {
        m_descriptor.layers.clear();
        for (auto const& lj : j["layers"]) {
            Project::LayerDescriptor ld;
            ld.name = lj.value("name", "Layer");
            ld.visible = lj.value("visible", true);
            ld.opacity = lj.value("opacity", 1.0f);
            ld.zIndex = lj.value("zIndex", 0);
            m_descriptor.layers.push_back(ld);
        }
    }

    // Rebuild tilemap
    RebuildTileMapFromDescriptor();

    // Load tileset usage
    if (j.contains("usedTileSets")) m_descriptor.usedTileSets = j["usedTileSets"].get<std::vector<std::string>>();

    // Load actual map grid into tilemap
    if (j.contains("tilemap")) {
        m_tileMap.FromJson(j["tilemap"]);
    }

    // portals
    m_portals.clear();
    if (j.contains("portals")) {
        for (auto const& pj : j["portals"]) {
            Portal p;
            p.id = pj.value("id", "");
            p.targetMap = pj.value("targetMap", "");
            p.srcX = pj.value("srcX", 0);
            p.srcY = pj.value("srcY", 0);
            p.dstX = pj.value("dstX", 0);
            p.dstY = pj.value("dstY", 0);
            m_portals.push_back(p);
        }
    }

    m_descriptor.loaded = true;
    return true;
}

bool Map::SaveToFile(const std::string& rootPath) const
{
    if (m_descriptor.relativePath.empty()) {
        std::cerr << "[Map] No relativePath set for map '" << m_descriptor.name << "'\n";
        return false;
    }
    fs::path path = fs::path(rootPath) / m_descriptor.relativePath;
    // Ensure directory exists
    if (path.has_parent_path()) fs::create_directories(path.parent_path());

    json j;
    j["name"] = m_descriptor.name;
    j["width"] = m_descriptor.width;
    j["height"] = m_descriptor.height;
    j["tileSize"] = m_descriptor.tileSize;

    // layers
    j["layers"] = json::array();
    for (auto const& ld : m_descriptor.layers) {
        json lj;
        lj["name"] = ld.name;
        lj["visible"] = ld.visible;
        lj["opacity"] = ld.opacity;
        lj["zIndex"] = ld.zIndex;
        j["layers"].push_back(lj);
    }

    j["usedTileSets"] = m_descriptor.usedTileSets;
    j["tilemap"] = m_tileMap.ToJson();

    j["portals"] = json::array();
    for (auto const& p : m_portals) {
        json pj;
        pj["id"] = p.id;
        pj["targetMap"] = p.targetMap;
        pj["srcX"] = p.srcX;
        pj["srcY"] = p.srcY;
        pj["dstX"] = p.dstX;
        pj["dstY"] = p.dstY;
        j["portals"].push_back(pj);
    }

    std::ofstream ofs(path);
    if (!ofs.is_open()) {
        std::cerr << "[Map] Failed to open file for writing: " << path.string() << "\n";
        return false;
    }
    ofs << j.dump(4);
    return true;
}

void Map::AddPortal(const Portal& p) { m_portals.push_back(p); }
bool Map::RemovePortalById(const std::string& id)
{
    auto it = std::remove_if(m_portals.begin(), m_portals.end(), [&](const Portal& p){ return p.id == id; });
    if (it != m_portals.end()) { m_portals.erase(it, m_portals.end()); return true; }
    return false;
}
std::vector<Portal> Map::GetPortals() const { return m_portals; }

} // namespace Editor::Map
