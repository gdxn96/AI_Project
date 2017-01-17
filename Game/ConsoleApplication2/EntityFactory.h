#pragma once
#include "GameObject.h"


class EntityFactory
{
public:
	static void CreateMissile(Vector2D position);
	static void CreateBullet(Vector2D position, Vector2D direction, bool enemyBullet=false);
	static void CreateMutant(Vector2D position);
	static void CreateMeteor();
	static void CreateAbductor(sf::Vector2f position);
	static void CreateNest(Vector2D pos, Vector2D dir, float speed);
	static void CreateAstronaut(float xPosition);
	static std::vector<GameObject*> getNewObjects();
	static std::vector<GameObject*> getNewObjectsBehind();
	static void clearObjects();
	static void abductorDeathNotify();

	static void initialize(sf::FloatRect levelSize);
private:
	static std::vector<GameObject*> m_newGameObjects;
	static std::vector<GameObject*> m_newGameObjectsBehind;
	static sf::FloatRect m_levelSize;

	static int m_numAbductors;
};

inline float RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

      