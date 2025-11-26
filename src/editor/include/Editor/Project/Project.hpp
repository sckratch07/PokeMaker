#ifndef _EDITOR_PROJECT_HPP__
#define _EDITOR_PROJECT_HPP__

/**
 * @file Project.hpp
 * @brief Structure avancée d'un projet pour l'éditeur.
 *
 * Cette version contient :
 *  - Des descriptors pour Map, TileSet, NPC et Shader
 *  - Gestion des chemins (rootPath) via std::filesystem
 *  - Fonctions utilitaires d'ajout / suppression / recherche
 *  - Méthode Update(float) (appelée par ProjectManager)
 *
 * La sérialisation vers / depuis JSON est prévue via ProjectSerializer.
 */

#include <string>
#include <vector>
#include <unordered_map>
#include <optional>
#include <filesystem>
#include <chrono>
#include <memory>
#include <algorithm>
#include <iostream>

namespace Editor::Project {

namespace fs = std::filesystem;

/**
 * @struct TileSetDescriptor
 * @brief Description d'un tileset (image + métadonnées).
 */
struct TileSetDescriptor
{
    std::string name;        ///< Nom logique du tileset
    std::string relativePath;///< Chemin relatif depuis le root du projet vers le fichier image
    int tileWidth  = 16;     ///< Largeur d'une tile en pixels
    int tileHeight = 16;     ///< Hauteur d'une tile en pixels
    int margin     = 0;      ///< marge (si présente dans l'image)
    int spacing    = 0;      ///< espacement entre tiles

    TileSetDescriptor() = default;
    TileSetDescriptor(std::string n, std::string rel, int w, int h)
        : name(std::move(n)), relativePath(std::move(rel)), tileWidth(w), tileHeight(h) {}
};

/**
 * @struct LayerDescriptor
 * @brief Métadonnées d'un layer dans une map.
 */
struct LayerDescriptor
{
    std::string name = "Layer";
    bool visible = true;
    float opacity = 1.0f;
    int zIndex = 0;
};

/**
 * @struct MapDescriptor
 * @brief Métadonnées d'une map (chemin, taille, layers, tilesets utilisés).
 */
struct MapDescriptor
{
    std::string name = "Map";
    std::string relativePath;          ///< Chemin relatif du fichier map (ex: maps/village.json)
    int width = 100;                   ///< largeur en tiles
    int height = 100;                  ///< hauteur en tiles
    int tileSize = 16;                 ///< taille d'une tile (carrée)
    std::vector<LayerDescriptor> layers;
    std::vector<std::string> usedTileSets; ///< noms des TileSetDescriptor référencés par la map
    // Données runtime optionnelles (non sérialisées par défaut) :
    bool loaded = false;

    MapDescriptor() = default;
    MapDescriptor(std::string n, std::string rel, int w, int h, int tsize = 16)
        : name(std::move(n)), relativePath(std::move(rel)), width(w), height(h), tileSize(tsize) {}
};

/**
 * @struct NPCDescriptor
 * @brief Description d'un NPC / entité éditable (chemin du fichier, type, meta).
 */
struct NPCDescriptor
{
    std::string id;              ///< identifiant unique dans le projet
    std::string relativePath;    ///< chemin relatif vers la définition (json/script)
    std::string displayName;     ///< nom affichable
    std::string type;            ///< ex: "shop", "enemy", "npc", "player"
    // Métadonnées libres
    std::unordered_map<std::string, std::string> meta;

    NPCDescriptor() = default;
    NPCDescriptor(std::string i, std::string rel, std::string name, std::string t)
        : id(std::move(i)), relativePath(std::move(rel)), displayName(std::move(name)), type(std::move(t)) {}
};

/**
 * @struct ShaderDescriptor
 * @brief Description d'un shader (vertex/fragment ou unique fragment) stocké dans le projet.
 */
struct ShaderDescriptor
{
    std::string name;
    std::string relativePath; ///< chemin relatif vers le fichier shader (ex: shaders/water.frag)
    std::unordered_map<std::string, std::string> uniforms; ///< meta pour valeurs par défaut (stockées en string)

    ShaderDescriptor() = default;
    ShaderDescriptor(std::string n, std::string rel) : name(std::move(n)), relativePath(std::move(rel)) {}
};

/**
 * @class Project
 * @brief Représentation complète d'un projet d'éditeur en mémoire.
 *
 * Construit pour être simple d'utilisation et sérialisable via ProjectSerializer.
 */
struct Project
{
    // Métadonnées du projet
    std::string name = "NewProject";
    std::string rootPath = ".";   ///< racine du projet (chemin sur disque)
    std::string description;      ///< description optionnelle

    // Collections de ressources (les chemins sont relatifs au rootPath)
    std::vector<MapDescriptor> maps;
    std::vector<TileSetDescriptor> tilesets;
    std::vector<NPCDescriptor> npcs;
    std::vector<ShaderDescriptor> shaders;

    // Paramètres généraux
    int tileSize = 16;            ///< valeur par défaut pour les maps nouvellement créées
    std::chrono::system_clock::time_point lastModified = std::chrono::system_clock::now();

    // ----- constructeurs -----
    Project() = default;

    // ----- gestion du chemin racine -----
    void SetRootPath(const std::string& path)
    {
        if (path.empty()) return;
        
        rootPath = path;
        // Normaliser
        try {
            rootPath = fs::weakly_canonical(fs::path(rootPath)).string();
        } catch (...) {
            // si canonical échoue, garder tel quel
        }
    }

    std::string GetRootPath() const
    {
        return rootPath;
    }

    /**
     * Résout un chemin relatif en chemin absolu basé sur rootPath.
     * Si le chemin est déjà absolu, retourne tel quel.
     */
    std::string ResolveAbsolutePath(const std::string& relativeOrAbsolute) const
    {
        fs::path p(relativeOrAbsolute);
        if (p.is_absolute()) return p.string();
        fs::path root(rootPath.empty() ? "." : rootPath);
        fs::path abs = fs::weakly_canonical(root / p);
        return abs.string();
    }

    /**
     * Transforme un chemin absolu en chemin relatif vis-à-vis du rootPath,
     * si possible. Si impossible, retourne le chemin absolu d'origine.
     */
    std::string MakeRelativeToRoot(const std::string& absolutePath) const
    {
        try {
            fs::path abs(absolutePath);
            fs::path rootP(rootPath.empty() ? "." : rootPath);
            abs = fs::weakly_canonical(abs);
            rootP = fs::weakly_canonical(rootP);

            // si abs et rootP ont la même racine, on relativise
            auto rel = fs::relative(abs, rootP);
            return rel.string();
        } catch (...) {
            return absolutePath;
        }
    }

    // ----- maps management -----
    MapDescriptor* AddMap(const std::string& name, const std::string& relativePath, int width, int height, int tsize = -1)
    {
        MapDescriptor map;
        map.name = name.empty() ? ("Map" + std::to_string(maps.size()+1)) : name;
        map.relativePath = relativePath;
        map.width = width;
        map.height = height;
        map.tileSize = (tsize <= 0) ? tileSize : tsize;
        maps.push_back(map);
        lastModified = std::chrono::system_clock::now();
        return &maps.back();
    }

    bool RemoveMapByPath(const std::string& relativePath)
    {
        auto it = std::remove_if(maps.begin(), maps.end(),
            [&](const MapDescriptor& m){ return m.relativePath == relativePath; });
        if (it != maps.end()) {
            maps.erase(it, maps.end());
            lastModified = std::chrono::system_clock::now();
            return true;
        }
        return false;
    }

    std::optional<std::reference_wrapper<MapDescriptor>> FindMapByPath(const std::string& relativePath)
    {
        for (auto& m : maps) {
            if (m.relativePath == relativePath) return m;
        }
        return std::nullopt;
    }

    std::optional<std::reference_wrapper<MapDescriptor>> FindMapByName(const std::string& name)
    {
        for (auto& m : maps) {
            if (m.name == name) return m;
        }
        return std::nullopt;
    }

    // ----- tilesets management -----
    TileSetDescriptor* AddTileSet(const std::string& name, const std::string& relativeImagePath, int tw = 16, int th = 16, int margin = 0, int spacing = 0)
    {
        TileSetDescriptor ts;
        ts.name = name.empty() ? ("TileSet" + std::to_string(tilesets.size()+1)) : name;
        ts.relativePath = relativeImagePath;
        ts.tileWidth = tw;
        ts.tileHeight = th;
        ts.margin = margin;
        ts.spacing = spacing;
        tilesets.push_back(ts);
        lastModified = std::chrono::system_clock::now();
        return &tilesets.back();
    }

    bool RemoveTileSetByName(const std::string& name)
    {
        auto it = std::remove_if(tilesets.begin(), tilesets.end(),
            [&](const TileSetDescriptor& t){ return t.name == name; });
        if (it != tilesets.end()) {
            tilesets.erase(it, tilesets.end());
            lastModified = std::chrono::system_clock::now();
            return true;
        }
        return false;
    }

    std::optional<std::reference_wrapper<TileSetDescriptor>> FindTileSetByName(const std::string& name)
    {
        for (auto& t : tilesets) {
            if (t.name == name) return t;
        }
        return std::nullopt;
    }

    // ----- NPC management -----
    NPCDescriptor* AddNPC(const std::string& id, const std::string& relativePath, const std::string& displayName, const std::string& type)
    {
        NPCDescriptor n(id, relativePath, displayName, type);
        npcs.push_back(std::move(n));
        lastModified = std::chrono::system_clock::now();
        return &npcs.back();
    }

    bool RemoveNPCById(const std::string& id)
    {
        auto it = std::remove_if(npcs.begin(), npcs.end(),
            [&](const NPCDescriptor& n){ return n.id == id; });
        if (it != npcs.end()) {
            npcs.erase(it, npcs.end());
            lastModified = std::chrono::system_clock::now();
            return true;
        }
        return false;
    }

    std::optional<std::reference_wrapper<NPCDescriptor>> FindNPCById(const std::string& id)
    {
        for (auto& n : npcs) {
            if (n.id == id) return n;
        }
        return std::nullopt;
    }

    // ----- shaders management -----
    ShaderDescriptor* AddShader(const std::string& name, const std::string& relativePath)
    {
        ShaderDescriptor s(name, relativePath);
        shaders.push_back(std::move(s));
        lastModified = std::chrono::system_clock::now();
        return &shaders.back();
    }

    bool RemoveShaderByName(const std::string& name)
    {
        auto it = std::remove_if(shaders.begin(), shaders.end(),
            [&](const ShaderDescriptor& s){ return s.name == name; });
        if (it != shaders.end()) {
            shaders.erase(it, shaders.end());
            lastModified = std::chrono::system_clock::now();
            return true;
        }
        return false;
    }

    std::optional<std::reference_wrapper<ShaderDescriptor>> FindShaderByName(const std::string& name)
    {
        for (auto& s : shaders) {
            if (s.name == name) return s;
        }
        return std::nullopt;
    }

    // ----- utilities -----
    /**
     * Retourne la liste des maps comme chemins absolus.
     */
    std::vector<std::string> GetAllMapAbsolutePaths() const
    {
        std::vector<std::string> out;
        out.reserve(maps.size());
        for (auto const& m : maps) out.push_back(ResolveAbsolutePath(m.relativePath));
        return out;
    }

    /**
     * Vérifie si une ressource existe sur le disque (chemin résolu).
     */
    bool ResourceExists(const std::string& relativeOrAbsolute) const
    {
        auto abs = ResolveAbsolutePath(relativeOrAbsolute);
        return fs::exists(fs::path(abs));
    }

    /**
     * Met à jour le timestamp lastModified et effectue éventuellement
     * du travail périodique (placeholder sûr, non intrusif).
     */
    void Update(float /*dt*/)
    {
        // Ici, on peut ajouter des tâches périodiques si souhaité.
        // Pour l'instant on met à jour le timestamp (non destructif).
        lastModified = std::chrono::system_clock::now();
    }

    // ----- debug helpers -----
    void DebugPrintSummary() const
    {
        std::cout << "Project: " << name << "\n";
        std::cout << "Root: " << rootPath << "\n";
        std::cout << "Maps: " << maps.size() << " TileSets: " << tilesets.size()
                  << " NPCs: " << npcs.size() << " Shaders: " << shaders.size() << "\n";
    }
};

} // namespace Editor::Project

#endif // _EDITOR_PROJECT_HPP__
