#pragma once
#include "GameObject.h"
#include "Camera.h"
#include <vector>

class CollisionManager
{
public:
	static bool Collides(GameObject* a, GameObject* b);
	static void RegisterEnemyBullet(GameObject* g);
	static void RegisterMeteor(GameObject* g);
	static void RegisterPlayerBullet(GameObject* g);
	static void RegisterEnemy(GameObject* g);
	static void deregisterGameObject(GameObject* g);
	static void CheckCollisions();
	static std::vector<GameObject*> GetObjectsOnScreen();

	static void RegisterCamera(Camera& cam);
private:
	static std::vector<GameObject*> m_playerBullets, 
									m_meteors,
									m_enemies,
									m_enemyBullets;
	static Camera* m_camera;
};
