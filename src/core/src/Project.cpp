#include "Core/Project.hpp"

namespace Core
{
void to_json(nlohmann::json& j, const Project& p)
{
    j = nlohmann::json::object();
    j["name"] = p.name;
    j["author"] = p.author;
    j["schema_version"] = p.schema_version;
    j["maps"] = nlohmann::json::array();
    for (const auto &m : p.maps) j["maps"].push_back(m);
    if (!p.meta.empty()) j["meta"] = p.meta;
}

void from_json(nlohmann::json& j, Project& p)
{
    p.name = j.value("name", std::string());
    p.author = j.value("author", std::string());
    p.schema_version = j.value("schema_version", std::string("1.0"));
    p.maps.clear();
    if (j.contains("maps") && j["maps"].is_array())
    {
        for (const auto &elem : j["maps"])
        {
            TileMap m;
            from_json(elem, m);
            p.maps.push_back(std::move(m));
        }
    }
    if (j.contains("meta") && j["meta"].is_object())
    {
        p.meta = j["meta"].get<std::map<std::string, nlohmann::json>>();
    }
    else
    {
        p.meta.clear();
    }
}
} // namespace core
