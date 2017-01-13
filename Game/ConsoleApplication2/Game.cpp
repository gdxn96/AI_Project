#include "stdafx.h"
#include "Game.h"
#include "Astronaut.h"

Game::Game(Vector2D screenSize, Vector2D levelSize) : 
	m_screenSize(screenSize),
	m_levelSize(levelSize), 
	m_camera(screenSize, levelSize)
{
	PhysicsManager::initialize(sf::FloatRect(0, screenSize.h * 1.f / 10, levelSize.w, screenSize.h * 7.f / 10));
	EntityFactory::initialize(sf::FloatRect(0, 0, levelSize.w, screenSize.h));
	float terrainPeak = screenSize.h * 7.f / 10;
	float terrainTrough = screenSize.h * 8.f / 10;
	std::vector<TerrainSegment*> terrainSegments = Terrain::GenerateTerrain(terrainPeak, terrainTrough, levelSize);
	m_terrainSegments.insert(m_terrainSegments.end(), terrainSegments.begin(), terrainSegments.end());

	EntityFactory::CreateNest(Vector2D(950, 530), Vector2D(0, 1), 150);

	for (int i = 0; i < 15; i++)
	{
		EntityFactory::CreateMeteor();
	}
	
	EntityFactory::CreateAstronaut(sf::Vector2f(950, screenSize.h - 150), sf::Vector2f(10, 20));

	Player* player = new Player(sf::Vector2f(950, 530),	//bounds
								sf::Vector2f(40, 20),	//size
								Vector2D(800, 800),		//acceleration
								Vector2D(5000, 400));	//maxSpeed

	m_gameObjects.push_back(player);
}

void Game::Update(float dt)
{
	vector<GameObject*> newObjects = EntityFactory::getNewObjects();
	vector<GameObject*> newObjectsBehind = EntityFactory::getNewObjectsBehind();
	if (newObjects.size() != 0)
	{
		m_gameObjects.insert(m_gameObjects.begin(), newObjects.begin(), newObjects.end());
	}
	if (newObjectsBehind.size() != 0)
	{
		m_gameObjectsBehind.insert(m_gameObjectsBehind.begin(), newObjectsBehind.begin(), newObjectsBehind.end());
	}

	EntityFactory::clearObjects();

	for (int i = m_gameObjects.size() - 1; i >= 0; i--)
	{
		GameObject* gameObject = m_gameObjects[i];

		if (gameObject->isAlive())
		{
			m_gameObjects[i]->Update(dt);
			m_gameObjects[i]->wrapPositions(m_camera);
		}
		else
		{
			m_gameObjects.erase(m_gameObjects.begin() + i);
		}
	}

	for (int i = m_gameObjectsBehind.size() - 1; i >= 0; i--)
	{
		GameObject* gameObject = m_gameObjectsBehind[i];

		if (gameObject->isAlive())
		{
			m_gameObjectsBehind[i]->Update(dt);
			m_gameObjectsBehind[i]->wrapPositions(m_camera);
		}
		else
		{
			m_gameObjectsBehind.erase(m_gameObjectsBehind.begin() + i);
		}
	}
}

void Game::Draw(sf::RenderWindow& r)
{
	m_camera.RenderObjects(r, m_gameObjectsBehind);
	m_camera.RenderObjects(r, m_terrainSegments);
	m_camera.RenderObjects(r, m_gameObjects);
}