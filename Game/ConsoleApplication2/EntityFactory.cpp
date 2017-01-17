#include "stdafx.h"
#include "EntityFactory.h"
#include "Missile.h"
#include "Bullet.h"
#include "Meteor.h"
#include "Astronaut.h"
#include "Nest.h"
#include "Abductor.h"
#include "Mutant.h"
#include "CollisionManager.h"

int EntityFactory::m_numAbductors = 0;
std::vector<GameObject*> EntityFactory::m_newGameObjects;
std::vector<GameObject*> EntityFactory::m_newGameObjectsBehind;
sf::FloatRect EntityFactory::m_levelSize = sf::FloatRect();

void EntityFactory::CreateBullet(Vector2D position, Vector2D direction, bool isEnemyBullet)
{
	auto bullet = new Bullet(position, direction);
	m_newGameObjects.push_back(bullet);

	if (!isEnemyBullet)
	{
		CollisionManager::RegisterPlayerBullet(bullet);
	}
	else
	{
		CollisionManager::RegisterEnemyBullet(bullet);
	}
}

void EntityFactory::CreateMissile(Vector2D position)
{
	m_newGameObjects.push_back(new Missile(position));
}

void EntityFactory::CreateMutant(Vector2D position)
{
	auto m = new Mutant(position);
	m_newGameObjects.push_back(m);
	CollisionManager::RegisterEnemy(m);
}

void EntityFactory::CreateMeteor()
{
	Vector2D position = Vector2D(RandomFloat(0, m_levelSize.width), -m_levelSize.width * 0.05f);
	float radius = RandomFloat(30, 80);
	float speed = RandomFloat(100, 200);  
	m_newGameObjectsBehind.push_back(new Meteor(position, radius, speed));
}

void EntityFactory::CreateAbductor(sf::Vector2f position)
{
	if (m_numAbductors < 20)
	{
		sf::Vector2f size(30, 30);
		float minPatrolHeight = m_levelSize.height * 0.75f;
		float maxPatrolHeight = m_levelSize.height * 0.6f;
		Abductor* abductor = new Abductor(position, size, minPatrolHeight, maxPatrolHeight);
		m_newGameObjects.push_back(abductor);
		AIManager::registerAbductor(abductor);

		m_numAbductors++;

		CollisionManager::RegisterEnemy(abductor);
	}
}

void EntityFactory::CreateAstronaut(float xPosition)
{
	sf::Vector2f position(xPosition, m_levelSize.height * 0.8f);
	sf::Vector2f size(10, 20);
	Astronaut* astronaut = new Astronaut(position, size);
	AIManager::registerAstronaut(astronaut);
	m_newGameObjects.push_back(astronaut);
}

void EntityFactory::CreateNest(Vector2D pos, Vector2D dir, float speed)
{
	auto nest = new Nest(pos, dir, speed);
	m_newGameObjects.push_back(nest);
	CollisionManager::RegisterEnemy(nest);
}

std::vector<GameObject*> EntityFactory::getNewObjects()
{
	return m_newGameObjects;
}

std::vector<GameObject*> EntityFactory::getNewObjectsBehind()
{
	return m_newGameObjectsBehind;
}

void EntityFactory::clearObjects()
{
	m_newGameObjects.clear();
	m_newGameObjectsBehind.clear();
}

void EntityFactory::abductorDeathNotify()
{
	m_numAbductors--;
}

void EntityFactory::initialize(sf::FloatRect levelSize)
{
	m_levelSize = levelSize;
}
