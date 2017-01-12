#pragma once
#include "GameObject.h"
#include "Bullet.h"
#include "Meteor.h"
#include "Astronaut.h"
#include "Abductor.h"

class GameObject;

class EntityFactory
{
public:
	static void CreateBullet(Vector2D position, Vector2D direction);
	static void CreateMutant();
	static void CreateMeteor(Vector2D position, float radius, float speed);
	static void CreateAbductor();
	static void CreateAstronaut(sf::Vector2f position, sf::Vector2f size);
	static void CreateNest();
	static std::vector<GameObject*> getNewObjects();
	static void clearObjects();
private:
	static std::vector<GameObject*> m_newGameObjects;
};
