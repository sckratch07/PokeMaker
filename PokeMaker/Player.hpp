#pragma once
#include "Entity.hpp"

class Player : public Entity
{
public:
	void handleinput();
private:
	float speed;
	sf::Sprite sprite;
};

