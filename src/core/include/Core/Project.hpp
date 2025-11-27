#ifndef _CORE_PROJECT_HPP__
#define _CORE_PROJECT_HPP__

#include "Core/TileMap.hpp"
#include <nlohmann/json.hpp>
#include <string>
#include <vector>


namespace Core
{
/**
* @brief Représente un project exporté/édité par l'Editor.
*/
struct Project {
    std::string name;
    std::string author;
    std::string schema_version = "1.0";
    std::vector<TileMap> maps;
    std::map<std::string, nlohmann::json> meta;
};

void to_json(nlohmann::json& j, const Project& p);
void from_json(const nlohmann::json& j, Project& p);

} // namespace core

#endif
