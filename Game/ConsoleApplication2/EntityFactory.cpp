#include "stdafx.h"
#include "EntityFactory.h"


std::vector<GameObject*> EntityFactory::m_newGameObjects;

void EntityFactory::CreateBullet(Vector2D position, Vector2D direction)
{
	m_newGameObjects.push_back(new Bullet(position, direction));
}

void EntityFactory::CreateMutant()
{
}

void EntityFactory::CreateMeteor()
{
}

void EntityFactory::CreateAbductor()
{
	//m_newGameObjects.push_back(new Abductor());
}

void EntityFactory::CreateAstronaut(sf::Vector2f position, sf::Vector2f size)
{
	m_newGameObjects.push_back(new Astronaut(position, size));
}

void EntityFactory::CreateNest()
{
}

std::vector<GameObject*> EntityFactory::getNewObjects()
{
	return m_newGameObjects;
}

void EntityFactory::clearObjects()
{
	m_newGameObjects.clear();
}
