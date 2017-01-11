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
	m_drawObjects.insert(m_drawObjects.begin(), terrainSegments.begin(), terrainSegments.end());

	//test meteor
	Meteor * m = new Meteor(30.f, 1000.f, Vector2D(1, 0), Vector2D(400, 400));
	m_drawObjects.push_back(m);
	m_updateObjects.push_back(m);
}

void Game::Update(float dt)
{
	int i = 0;
	for (GameObject* gameObject : m_updateObjects)
	{
		gameObject->Update(dt);
		gameObject->wrapPositions(m_camera);
	}
}

void Game::Draw(sf::RenderWindow & r)
{
	m_camera.RenderObjects(r, m_drawObjects);
}
