#include "stdafx.h"
#include "EntityFactory.h"

void EntityFactory::CreateBullet()
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

void EntityFactory::CreateSwarm()
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
