#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "GameObject.h"
#include "Terrain.h"
#include "Camera.h"

class Game
{
public:
	Game(Vector2D screenSize, Vector2D levelSize);
	void Update(float dt);
	void Draw(sf::RenderWindow& r);
	Camera m_camera; //testing
private:
	std::vector<GameObject*> m_gameObjects;
	//Camera m_camera;
	Vector2D m_screenSize, m_levelSize;
};