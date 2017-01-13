#include "stdafx.h"
#include "EntityFactory.h"


std::vector<GameObject*> EntityFactory::m_newGameObjects;

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

void EntityFactory::CreateMeteor(Vector2D position, float radius, float speed)
{
	m_newGameObjects.push_back(new Meteor(position, radius, speed));
}

void EntityFactory::CreateAbductor(sf::Vector2f position)
{
	Abductor* abductor = new Abductor(position, sf::Vector2f(30, 30), 450, 580);
	m_newGameObjects.push_back(abductor);
}

void EntityFactory::CreateAstronaut(sf::Vector2f position)
{
	Astronaut* astronaut = new Astronaut(position, sf::Vector2f(10, 20));
	AIManager::registerAstronaut(astronaut);
	m_newGameObjects.push_back(astronaut);
}

void EntityFactory::CreateNest(Vector2D pos, Vector2D dir, float speed)
{
	m_newGameObjects.push_back(new Nest(pos, dir, speed));
}

std::vector<GameObject*> EntityFactory::getNewObjects()
{
	return m_newGameObjects;
}

void EntityFactory::clearObjects()
{
	m_newGameObjects.clear();
}
