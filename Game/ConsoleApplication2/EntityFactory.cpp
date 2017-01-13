#include "stdafx.h"
#include "EntityFactory.h"


std::vector<GameObject*> EntityFactory::m_newGameObjects;
std::vector<GameObject*> EntityFactory::m_newGameObjectsBehind;
sf::FloatRect EntityFactory::m_levelSize = sf::FloatRect();

void EntityFactory::CreateBullet(Vector2D position, Vector2D direction)
{
	m_newGameObjects.push_back(new Bullet(position, direction));
}

void EntityFactory::CreateMissile()
{
}

void EntityFactory::CreateMutant()
{
}

void EntityFactory::CreateMeteor()
{
	Vector2D position = Vector2D(RandomFloat(0, m_levelSize.width), -m_levelSize.width * 0.05f);
	float radius = RandomFloat(30, 80);
	float speed = RandomFloat(100, 200);  
	m_newGameObjectsBehind.push_back(new Meteor(position, radius, speed));
}

void EntityFactory::CreateAbductor()
{
	//m_newGameObjects.push_back(new Abductor());
}

void EntityFactory::CreateAstronaut(sf::Vector2f position, sf::Vector2f size)
{
	m_newGameObjects.push_back(new Astronaut(position, size));
}

void EntityFactory::CreateNest(Vector2D pos, Vector2D dir, float speed)
{
	m_newGameObjects.push_back(new Nest(pos, dir, speed));
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

void EntityFactory::initialize(sf::FloatRect levelSize)
{
	m_levelSize = levelSize;
}
