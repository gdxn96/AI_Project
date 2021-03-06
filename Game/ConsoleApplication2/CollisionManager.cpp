#include "stdafx.h"
#include "CollisionManager.h"
 
std::vector<GameObject*> CollisionManager::m_playerBullets;
std::vector<GameObject*> CollisionManager::m_meteors;
std::vector<GameObject*> CollisionManager::m_enemies;
std::vector<GameObject*> CollisionManager::m_enemyBullets;
std::vector<GameObject*> CollisionManager::m_powerups;

Player* CollisionManager::m_player = nullptr;
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

void CollisionManager::RegisterPowerup(GameObject* powerup)
{
	m_powerups.push_back(powerup);
}

void CollisionManager::RegisterPlayer(GameObject* player)
{
	m_player = dynamic_cast<Player*>(player);
}

void CollisionManager::deregisterGameObject(GameObject * g)
{
	if (dynamic_cast<Player*>(g) == NULL)
	{
		m_enemies.erase(std::remove(m_enemies.begin(), m_enemies.end(), g), m_enemies.end());
		m_playerBullets.erase(std::remove(m_playerBullets.begin(), m_playerBullets.end(), g), m_playerBullets.end());
		m_meteors.erase(std::remove(m_meteors.begin(), m_meteors.end(), g), m_meteors.end());
		m_enemyBullets.erase(std::remove(m_enemyBullets.begin(), m_enemyBullets.end(), g), m_enemyBullets.end());
		m_powerups.erase(std::remove(m_powerups.begin(), m_powerups.end(), g), m_powerups.end());
	}
	else
	{
		m_player = nullptr;
	}
}


void CollisionManager::CheckCollisions()
{
	for (GameObject* bullet : m_playerBullets)
	{
		for (GameObject* enemy : m_enemies)
		{
			if (Collides(enemy, bullet))
			{
				Damageable* b = dynamic_cast<Damageable*>(bullet);
				enemy->Damage(b->getDamage());
				bullet->kill();
				break;
			}
		}
	}

	
	for (GameObject* bullet : m_enemyBullets)
	{
		if (m_player != nullptr)
		if (Collides(m_player, bullet))
		{
			if (m_player->isInvincible() == false)
			{
				cout << "getting damaged" << endl;
				Damageable* b = dynamic_cast<Damageable*>(bullet);
				m_player->Damage(b->getDamage());
			}
			bullet->kill();
			break;
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
		if (m_player != nullptr)
		{
			if (Collides(m_player, meteor))
			{
				m_player->kill();
			}
		}
	}

	if (m_player != nullptr)
	{
		for (GameObject* powerup : m_powerups)
		{
			if (Collides(m_player, powerup))
			{
				PowerUp* p = dynamic_cast<PowerUp*>(powerup);

				switch (p->GetType())
				{
				case PowerUpTypes::HYPERJUMP:
					m_player->addHyperJumpPowerUp();
					break;
				case PowerUpTypes::MORE_FIRE_RATE:
					m_player->increaseFireRate();
					break;
				case PowerUpTypes::INVINCIBILITY:
					m_player->makeInvincible();
					break;
				case PowerUpTypes::EMP:
					m_player->addEMP();
					break;
				}

				powerup->kill();
			}
		}
	}
}

std::vector<GameObject*> CollisionManager::GetObjectsOnScreen()
{
	std::vector<GameObject*> objects;
	std::vector<GameObject*> enemiesOnScreen = m_camera->getObjectsInViewPort(m_enemies);
	std::vector<GameObject*> enemyBulletsOnScreen = m_camera->getObjectsInViewPort(m_enemyBullets);

	objects.insert(objects.end(), enemiesOnScreen.begin(), enemiesOnScreen.end());
	objects.insert(objects.end(), enemyBulletsOnScreen.begin(), enemyBulletsOnScreen.end());

	return objects;
}

std::vector<GameObject*> CollisionManager::GetEnemiesOnScreen()
{
	return m_camera->getObjectsInViewPort(m_enemies);
}

void CollisionManager::RegisterCamera(Camera & cam)
{
	m_camera = &(cam);
}
