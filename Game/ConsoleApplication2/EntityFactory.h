#pragma once
#include "GameObject.h"
#include "Bullet.h"
#include "Meteor.h"
#include "Astronaut.h"
#include "Nest.h"
#include "Abductor.h"
#include "Mutant.h"

class EntityFactory
{
public:
	static void CreateMissile(Vector2D position);
	static void CreateBullet(Vector2D position, Vector2D direction);
	static void CreateMutant();
	static void CreateMeteor();
	static void CreateAbductor(sf::Vector2f position);
	static void CreateNest(Vector2D pos, Vector2D dir, float speed);
	static void CreateAstronaut(sf::Vector2f position);
	static std::vector<GameObject*> getNewObjects();
	static std::vector<GameObject*> getNewObjectsBehind();
	static void clearObjects();

	static void initialize(sf::FloatRect levelSize);
private:
	static std::vector<GameObject*> m_newGameObjects;
	static std::vector<GameObject*> m_newGameObjectsBehind;
	static sf::FloatRect m_levelSize;
};

inline float RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

      