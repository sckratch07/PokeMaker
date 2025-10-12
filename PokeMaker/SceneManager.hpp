#pragma once
#include <map>
#include "TileMap.hpp"
#include "Player.hpp"

class SceneManager
{
public:
	void loadMap(std::string id);
	void linkMaps(TileMap& map, TileMap& dungeon, sf::Vector2f enter, sf::Vector2f exit);
	inline TileMap* getCurrentScene()
		{ return currentScene; }
private:
	TileMap* currentScene = nullptr;
	std::map<std::string, TileMap> loadedMaps;
};

