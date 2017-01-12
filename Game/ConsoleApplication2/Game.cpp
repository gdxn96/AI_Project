#include "stdafx.h"
#include "Game.h"
#include "Astronaut.h"

Game::Game(Vector2D screenSize, Vector2D levelSize) : 
	m_screenSize(screenSize),
	m_levelSize(levelSize), 
	m_camera(screenSize, levelSize)
{
	PhysicsManager::initialize(sf::FloatRect(0, screenSize.h * 1.f / 10, levelSize.w, screenSize.h * 7.f / 10));

	float terrainPeak = screenSize.h * 7.f / 10;
	float terrainTrough = screenSize.h * 8.f / 10;

	std::vector<TerrainSegment*> terrainSegments = Terrain::GenerateTerrain(terrainPeak, terrainTrough, levelSize);
	m_drawObjects.insert(m_drawObjects.begin(), terrainSegments.begin(), terrainSegments.end());

	//test meteor
	Meteor * m = new Meteor(30.f, 1000.f, Vector2D(1, 0), Vector2D(400, 400));
	m_drawObjects.push_back(m);
	m_updateObjects.push_back(m);

	Astronaut * a = new Astronaut(Vector2D(950, screenSize.h - 150), true);
	m_drawObjects.push_back(a);
	m_updateObjects.push_back(a);

	Player* player = new Player(Vector2D(950, 530),	//bounds
		Vector2D(800, 800),							//accel
		Vector2D(400, 400),							//maxSpeed
		true);										//isMiniMapObject

	EntityFactory::CreateNest(Vector2D(950, 530), Vector2D(0, 1), 150);

	InputManager* input = InputManager::getInstance();

	input->AddListener(static_cast<int>(EventListener::KeyDownEvent::UP), player);
	input->AddListener(static_cast<int>(EventListener::KeyDownEvent::LEFT), player);
	input->AddListener(static_cast<int>(EventListener::KeyDownEvent::DOWN), player);
	input->AddListener(static_cast<int>(EventListener::KeyDownEvent::RIGHT), player);
	input->AddListener(static_cast<int>(EventListener::KeyUpEvent::UP), player);
	input->AddListener(static_cast<int>(EventListener::KeyUpEvent::LEFT), player);
	input->AddListener(static_cast<int>(EventListener::KeyUpEvent::DOWN), player);
	input->AddListener(static_cast<int>(EventListener::KeyUpEvent::RIGHT), player);
	input->AddListener(static_cast<int>(EventListener::GenericEvent::SHOOT), player);
	input->AddListener(static_cast<int>(EventListener::GenericEvent::NO_SHOOT), player);

	m_drawObjects.push_back(player);
	m_updateObjects.push_back(player);
}

void Game::Update(float dt)
{
	int i = 0;
	for (GameObject* gameObject : m_updateObjects)
	{
		gameObject->Update(dt);
		gameObject->wrapPositions(m_camera);
	}
	vector<GameObject*> newObjects = EntityFactory::getNewObjects();

	if (newObjects.size() != 0)
	{
		m_drawObjects.insert(m_drawObjects.end(), newObjects.begin(), newObjects.end());
		m_updateObjects.insert(m_updateObjects.end(), newObjects.begin(), newObjects.end());
		EntityFactory::clearObjects();
	}
}

void Game::Draw(sf::RenderWindow& r)
{
	m_camera.RenderObjects(r, m_drawObjects);
}