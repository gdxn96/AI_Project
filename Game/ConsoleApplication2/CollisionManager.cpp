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
	std::remove(m_enemies.begin(), m_enemies.end(), g);
	std::remove(m_playerBullets.begin(), m_playerBullets.end(), g);
	std::remove(m_meteors.begin(), m_meteors.end(), g);
	std::remove(m_enemyBullets.begin(), m_enemyBullets.end(), g);
}

void CollisionManager::CheckCollisions()
{
	for (auto& bullet : m_playerBullets)
	{
		for (auto& enemy : m_enemies)
		{
			if (Collides(enemy, bullet))
			{
				enemy->kill();
				bullet->kill();
			}
		}
	}
}

void CollisionManager::RegisterCamera(Camera & cam)
{
	m_camera = &(cam);
}
