#include "stdafx.h"
#include "Game.h"

Game::Game(Vector2D screenSize, Vector2D levelSize) : 
	m_screenSize(screenSize),
	m_levelSize(levelSize), 
	m_camera(screenSize, levelSize)
{
	float terrainPeak = screenSize.h * 7.f / 10;
	float terrainTrough = screenSize.h * 8.f / 10;
	std::vector<TerrainSegment*> terrainSegments = Terrain::GenerateTerrain(terrainPeak, terrainTrough, levelSize);
	m_gameObjects.insert(m_gameObjects.begin(), terrainSegments.begin(), terrainSegments.end());
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
