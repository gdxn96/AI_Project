#pragma once
#include "GameObject.h"
#include "Bullet.h"
#include "Meteor.h"
#include "Astronaut.h"
#include "Nest.h"
#include "Abductor.h"

class EntityFactory
{
public:
	static void CreateMissile();
	static void CreateBullet(Vector2D position, Vector2D direction);
	static void CreateMutant();
	static void CreateMeteor(Vector2D position, float radius, float speed);
	static void CreateAbductor(sf::Vector2f position);
	static void CreateNest(Vector2D pos, Vector2D dir, float speed);
	static void CreateAstronaut(sf::Vector2f position);
	static std::vector<GameObject*> getNewObjects();
	static void clearObjects();
private:
	static std::vector<GameObject*> m_newGameObjects;
};
      