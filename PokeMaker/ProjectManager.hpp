#pragma once
#include "SFML/Graphics.hpp"
#include "JsonUtils.hpp"

struct MapInfo
{
	std::string id;
	std::string path;
};

struct PlayerInfo
{
	sf::Vector2f spawn;
	std::string spritePath;
};

struct ProjectData
{
	std::string projectName = "null";
	std::vector<MapInfo> maps;
	PlayerInfo playerInfo;
};

class ProjectManager
{
public:
	void createProject(std::string name, std::string path);
	void loadProject(std::string path);
	void saveProject();
	inline ProjectData& getCurrentProject() { return this->currentProjectData; }
	inline bool& projectLoaded() { return this->projectLoad; }
private:
	std::string currentProjectPath;
	ProjectData currentProjectData;
	bool projectLoad = false;
};