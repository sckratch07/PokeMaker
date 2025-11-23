#include "Editor/Project.hpp"

namespace Editor {

Project::Project(const std::string& name)
    : name(name)
{
}

std::shared_ptr<Map> Project::getMap(const std::string& mapName)
{
    for (auto& m : maps)
        if (m->name == mapName)
            return m;
    return nullptr;
}

nlohmann::json Project::toJson() const
{
    nlohmann::json j;
    j["name"] = name;
    j["maps"] = nlohmann::json::array();

    for (auto& m : maps)
        j["maps"].push_back(m->toJson());

    return j;
}

void Project::fromJson(const nlohmann::json& j)
{
    name = j.at("name").get<std::string>();

    maps.clear();
    for (auto& jm : j.at("maps"))
    {
        auto map = std::make_shared<Map>();
        map->fromJson(jm);
        maps.push_back(map);
    }
}

} // namespace Editor
