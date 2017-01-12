#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "Player.h"
#include "InputManager.h"
#include "Terrain.h"
#include "Camera.h"
#include "Meteor.h"
#include "EntityFactory.h"
#include "PhysicsManager.h"

class Game
{
public:
	Game(Vector2D screenSize, Vector2D levelSize);
	void Update(float dt);
	void Draw(sf::RenderWindow& r);

private:
	std::vector<GameObject*> m_gameObjects;
	std::vector<GameObject*> m_terrainSegments;
	Camera m_camera;
	Vector2D m_screenSize, m_levelSize;
};