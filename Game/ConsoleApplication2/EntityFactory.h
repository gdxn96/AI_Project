#pragma once
#include "GameObject.h"
#include "Bullet.h"
#include "Meteor.h"
#include "Astronaut.h"
#include "Nest.h"

class EntityFactory
{
public:
	static void CreateBullet();
	static void CreateMissile();
	static void CreateMutant();
	static void CreateMeteor();
	static void CreateAbductor();
	static void CreateNest(Vector2D pos, Vector2D dir, float speed);
	static std::vector<GameObject*> getNewObjects();
	static void clearObjects();
private:
	static std::vector<GameObject*> m_newGameObjects;
};
      