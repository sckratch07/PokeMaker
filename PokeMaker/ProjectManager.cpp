#include "ProjectManager.hpp"
#include <fstream>

void to_json(json& j, const MapInfo& m)
{
	j = json{
		{"id", m.id},
		{"path", m.path}
	};
}

void from_json(const json& j, MapInfo& m)
{
	m.id = j["id"];
	m.path = j["path"];
}

void ProjectManager::createProject(std::string name, std::string path)
{
	this->currentProjectPath = path;

	std::vector<MapInfo> mapBaseData;

	json baseData;
	baseData["projectName"] = name;
	baseData["maps"] = mapBaseData;
	baseData["playerSpawnX"] = 0.f;
	baseData["playerSpawnY"] = 0.f;
	baseData["spritePath"] = "../assets/";
	JsonUtils::saveJSON(path, baseData);

	this->currentProjectData.projectName = baseData["projectName"];
	this->currentProjectData.maps = baseData["maps"];
	this->currentProjectData.playerInfo.spawn.x = baseData["playerSpawnX"];
	this->currentProjectData.playerInfo.spawn.x = baseData["playerSpawnY"];
	this->currentProjectData.playerInfo.spritePath = baseData["spritePath"];

	this->projectLoad = true;
}

void ProjectManager::loadProject(std::string path)
{
	this->currentProjectPath = path;

	json dataLoaded = JsonUtils::loadJSON(path);
	this->currentProjectData.projectName = dataLoaded["projectName"];
	this->currentProjectData.maps = dataLoaded["maps"];
	this->currentProjectData.playerInfo.spawn.x = dataLoaded["playerSpawnX"];
	this->currentProjectData.playerInfo.spawn.x = dataLoaded["playerSpawnY"];
	this->currentProjectData.playerInfo.spritePath = dataLoaded["spritePath"];

	this->projectLoad = true;
}

void ProjectManager::saveProject()
{
	json baseData;
	baseData["projectName"] = this->currentProjectData.projectName;
	baseData["maps"] = this->currentProjectData.maps;
	baseData["playerSpawnX"] = this->currentProjectData.playerInfo.spawn.x;
	baseData["playerSpawnY"] = this->currentProjectData.playerInfo.spawn.y;
	baseData["spritePath"] = this->currentProjectData.playerInfo.spritePath;
	JsonUtils::saveJSON(this->currentProjectPath, baseData);
}
