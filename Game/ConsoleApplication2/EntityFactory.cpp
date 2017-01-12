#include "stdafx.h"
#include "EntityFactory.h"

std::vector<GameObject*> EntityFactory::m_newGameObjects;
void EntityFactory::CreateBullet()
{
}

void EntityFactory::CreateMissile()
{
}

void EntityFactory::CreateMutant()
{
}

void EntityFactory::CreateMeteor()
{
}

void EntityFactory::CreateAbductor()
{
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
