#include "stdafx.h"
#include "Game.h"
#include "Astronaut.h"

Game::Game(Vector2D screenSize, Vector2D levelSize) : 
	m_screenSize(screenSize),
	m_levelSize(levelSize), 
	m_camera(screenSize, levelSize)
{
	float terrainPeak = screenSize.h * 7.f / 10;
	float terrainTrough = screenSize.h * 8.f / 10;

	m_gameObjects.push_back(new Terrain(terrainPeak, terrainTrough, levelSize));
	m_gameObjects.push_back(new Astronaut(Rect(950, screenSize.h - 150, 10, 20), true));
}

void Game::Update(float dt)
{
	for (GameObject* gameObject : m_gameObjects)
	{
		gameObject->Update(dt);
	}
}

void Game::Draw(sf::RenderWindow & r)
{
	m_camera.RenderObjects(r, m_gameObjects);
}
