#include "stdafx.h"
#include "CollisionManager.h"

std::vector<GameObject*> 
CollisionManager::m_playerBullets,
CollisionManager::m_meteors,
CollisionManager::m_enemies,
CollisionManager::m_enemyBullets;

Camera* CollisionManager::m_camera = nullptr;

bool CollisionManager::Collides(GameObject * a, GameObject * b)
{
	return a->getAABB().intersects(b->getAABB());
}

void CollisionManager::RegisterEnemyBullet(GameObject * g)
{
	m_enemyBullets.push_back(g);
}

void CollisionManager::RegisterMeteor(GameObject * g)
{
	m_meteors.push_back(g);
}

void CollisionManager::RegisterPlayerBullet(GameObject * g)
{
	m_playerBullets.push_back(g);
}

void CollisionManager::RegisterEnemy(GameObject * g)
{
	m_enemies.push_back(g);
}

void CollisionManager::deregisterGameObject(GameObject * g)
{
	m_enemies.erase(std::remove(m_enemies.begin(), m_enemies.end(), g), m_enemies.end());
	m_playerBullets.erase(std::remove(m_playerBullets.begin(), m_playerBullets.end(), g), m_playerBullets.end());
	m_meteors.erase(std::remove(m_meteors.begin(), m_meteors.end(), g), m_meteors.end());
	m_enemyBullets.erase(std::remove(m_enemyBullets.begin(), m_enemyBullets.end(), g), m_enemyBullets.end());
}


void CollisionManager::CheckCollisions()
{
	for (GameObject* bullet : m_playerBullets)
	{
		for (GameObject* enemy : m_enemies)
		{
			if (Collides(enemy, bullet))
			{
				enemy->kill();
				bullet->kill();
				break;
			}
		}
	}

	for (GameObject* meteor : m_meteors)
	{
		for (GameObject* enemy : m_enemies)
		{
			if (Collides(enemy, meteor))
			{
				enemy->kill();
			}
		}
	}
}

void CollisionManager::RegisterCamera(Camera & cam)
{
	m_camera = &(cam);
}
