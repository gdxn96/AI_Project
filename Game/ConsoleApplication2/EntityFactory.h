#pragma once
#include "GameObject.h"
#include "Bullet.h"
#include "Meteor.h"
#include "Astronaut.h"

class EntityFactory
{
public:
	static void CreateBullet();
	static void CreateMutant();
	static void CreateMeteor();
	static void CreateAbductor();
	static void CreateNest();
	static std::vector<GameObject*> getNewObjects();
	static void clearObjects();
private:
	static std::vector<GameObject*> m_newGameObjects;
};
