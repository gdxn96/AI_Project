#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "Player.h"
#include "InputManager.h"

class Game
{
private:
	std::vector<GameObject*> m_gameObjects;

public:
	Game();
	void Update(float dt);
	void Draw(sf::RenderWindow& r);
};