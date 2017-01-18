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
#include "PowerUpManager.h"

class Game
{
public:
	Game(Vector2D screenSize, Vector2D levelSize);
	void CreatePlayer();
	void CreateEntities(Vector2D screenSize);
	void Update(float dt);
	void RestartGame();
	void UpdateGameObjectList(float dt, std::vector<GameObject*>& list);
	void AddNewGameObjects();
	void Draw(sf::RenderWindow& r);

private:
	std::vector<GameObject*> m_gameObjects, m_gameObjectsBehind;
	std::vector<GameObject*> m_terrainSegments;
	Camera m_camera;
	Vector2D m_screenSize, m_levelSize;
	PowerUpManager m_powerupManager;
	Player* m_player;
};