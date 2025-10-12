#include "SceneManager.hpp"
#include "Application.hpp"

extern Application game;

void SceneManager::loadMap(std::string id)
{
	ProjectData& project = game.getProjectManager().getCurrentProject();

	TileMap map;
	if (this->loadedMaps.contains(id))
	{
		map.loadFromFile(project.maps[std::stoi(id)].path);
		this->loadedMaps[id] = map;
	}
	else map = this->loadedMaps[id];

	this->currentScene = &map;
}

void SceneManager::linkMaps(TileMap& map, TileMap& dungeon, sf::Vector2f enter, sf::Vector2f exit)
{
	MapLink mapDungeon = { dungeon, enter };
	MapLink dungeonMap = { map, exit };

	map.addLinks(mapDungeon);
	dungeon.addLinks(dungeonMap);
}
