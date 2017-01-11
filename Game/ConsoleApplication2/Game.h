#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "Player.h"
#include "InputManager.h"
#include "Terrain.h"
#include "Camera.h"

class Game
{
private:
	std::vector<GameObject*> m_gameObjects;
	Vector2D m_screenSize; 
	Vector2D m_levelSize;

public:
	Camera m_camera; //testing

	Game(Vector2D screenSize, Vector2D levelSize);
	void Update(float dt);
	void Draw(sf::RenderWindow& r);
};