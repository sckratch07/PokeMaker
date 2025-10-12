#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

typedef struct MapLink MapLink;

struct Tile
{
	int id;
	sf::IntRect textureCoords;
	bool collision;
};

class TileLayer
{
	std::string name;
	std::vector<Tile> tiles;
};

class TileMap
{
public:
	void loadFromFile(std::string file);
	void saveToFile(std::string file);
	void render(sf::RenderTarget& target);

	inline void addLinks(MapLink& link)
		{ this->links.push_back(link); }
	inline void setTileSetPath(std::string path)
		{ this->tilesetPath = path; }
	inline void setMapSize(int width, int height)
		{ this->width = width; this->height = height; }
	inline void setTileSize(int width, int height)
		{ this->tileSize.x = width; this->tileSize.y = height; }
private:
	int width;
	int height;
	sf::Vector2i tileSize;
	std::vector<TileLayer> tiles;
	std::string tilesetPath;
	std::vector<MapLink> links;
};

struct MapLink
{
	TileMap targetMap;
	sf::Vector2f enter;
};
