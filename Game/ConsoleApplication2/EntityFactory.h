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
	static void CreateMutant(Vector2D position, Vector2D size);
	static void CreateMeteor();
	static void CreateAbductor(sf::Vector2f position);
	static void CreateNest(Vector2D pos, Vector2D dir, float speed);
	static void CreateAstronaut(float xPosition);
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

      