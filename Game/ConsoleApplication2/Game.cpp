#include "stdafx.h"
#include "Game.h"
#include "Astronaut.h"
#include "CollisionManager.h"

Game::Game(Vector2D screenSize, Vector2D levelSize) : 
	m_screenSize(screenSize),
	m_levelSize(levelSize), 
	m_camera(screenSize, levelSize)
{
	sf::FloatRect levelBounds(0, screenSize.h * 1.f / 10, levelSize.w, screenSize.h * 7.f / 10);
	AIManager::initialize(levelBounds);
	PhysicsManager::initialize(levelBounds);
	EntityFactory::initialize(sf::FloatRect(0, 0, levelSize.w, screenSize.h));
	float terrainPeak = screenSize.h * 7.f / 10;
	float terrainTrough = screenSize.h * 8.f / 10;
	std::vector<TerrainSegment*> terrainSegments = Terrain::GenerateTerrain(terrainPeak, terrainTrough, levelSize);
	m_terrainSegments.insert(m_terrainSegments.end(), terrainSegments.begin(), terrainSegments.end());
	CreatePlayer();
	CreateEntities(screenSize);
	CollisionManager::RegisterCamera(m_camera);
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
	EntityFactory::CreateNest(Vector2D(950, 530), Vector2D(0, 1), 500);

	for (int i = 0; i < 15; i++)
	{
		if (i % 2 == 0)
			EntityFactory::CreateAstronaut(400 + (i * 30));

		EntityFactory::CreateMeteor();
		EntityFactory::CreateMutant(Vector2D(RandomFloat(0, m_levelSize.width), 0));
	}
}


void Game::Update(float dt)
{
	AIManager::process();
	AddNewGameObjects();
	UpdateGameObjectList(dt, m_gameObjects);
	UpdateGameObjectList(dt, m_gameObjectsBehind);

	CollisionManager::CheckCollisions();
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
	for (auto& it = list.begin(); it != list.end(); )
	{
		if (!(*it)->isAlive())
		{
			delete * it;
			it = list.erase(it);
			CollisionManager::deregisterGameObject(*(it));
		}
		else 
		{
			(*it)->Update(dt);
			(*it)->wrapPositions(m_camera);
			++it;
		}
	}
}


void Game::Draw(sf::RenderWindow& r)
{
	m_camera.RenderObjects(r, m_gameObjectsBehind);
	m_camera.RenderObjects(r, m_terrainSegments);
	m_camera.RenderObjects(r, m_gameObjects);
}