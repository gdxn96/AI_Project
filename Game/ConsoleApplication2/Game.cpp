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
	CreatePlayer();
	CreateEntities(screenSize);
}


void Game::CreatePlayer()
{
	Player* player = new Player(
		sf::Vector2f(950, 530),	//bounds
		sf::Vector2f(40, 20),	//size
		Vector2D(800, 800),		//acceleration
		Vector2D(5000, 400)		//maxSpeed
	);

	AIManager::registerPlayer(player);
	m_gameObjects.push_back(player);
}

void Game::CreateEntities(Vector2D screenSize)
{
	EntityFactory::CreateNest(Vector2D(950, 530), Vector2D(0, 1), 150);
	EntityFactory::CreateAbductor(sf::Vector2f(800, 200));
	EntityFactory::CreateAbductor(sf::Vector2f(700, 200));

	for (int i = 0; i < 15; i++)
	{
		if (i % 2 == 0)
			EntityFactory::CreateAstronaut(400 + (i * 30));
		//EntityFactory::CreateAstronaut(800 + (i * 30));
		EntityFactory::CreateAbductor(sf::Vector2f(750, 200));
		EntityFactory::CreateMeteor();
	}
}


void Game::Update(float dt)
{
	AIManager::process();
	AddNewGameObjects();
	UpdateGameObjectList(dt, m_gameObjects);
	UpdateGameObjectList(dt, m_gameObjectsBehind);
}


void Game::AddNewGameObjects()
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
}


void Game::UpdateGameObjectList(float dt, std::vector<GameObject*>& list)
{
	for (int i = list.size() - 1; i >= 0; i--)
	{
		GameObject* gameObject = list[i];

		if (gameObject->isAlive())
		{
			list[i]->Update(dt);
			list[i]->wrapPositions(m_camera);
		}
		else
		{
			list.erase(list.begin() + i);
		}
	}
}


void Game::Draw(sf::RenderWindow& r)
{
	m_camera.RenderObjects(r, m_gameObjectsBehind);
	m_camera.RenderObjects(r, m_terrainSegments);
	m_camera.RenderObjects(r, m_gameObjects);
}