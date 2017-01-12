#include "stdafx.h"
#include "EntityFactory.h"

std::vector<GameObject*> EntityFactory::m_newGameObjects;
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
