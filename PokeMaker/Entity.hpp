#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

class Entity
{
public:
	void update(float dt);
	void render(sf::RenderTarget& target);
private:
	std::string id;
	sf::Vector2f position;
};

