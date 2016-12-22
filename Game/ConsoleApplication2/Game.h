#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "Player.h"

class Game
{
public:
	Game();

	void Update(float dt);
	void Draw(sf::RenderWindow& r);

private:
	std::vector<GameObject*> m_gameObjects;
};