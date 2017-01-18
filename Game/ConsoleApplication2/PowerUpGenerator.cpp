#include "stdafx.h"
#include "PowerUpGenerator.h"


PowerUpGenerator::PowerUpGenerator(int powerupType, int minSpawnTime, int maxSpawnTime)
	: MIN_SPAWN_TIME(minSpawnTime),
	  MAX_SPAWN_TIME(maxSpawnTime),
	  TYPE(powerupType)
{
	m_timeTillSpawn = 0;
	ResetTimeTillSpawn();
}


PowerUpGenerator::~PowerUpGenerator()
{
}

void PowerUpGenerator::Update(float dt)
{
	m_timeTillSpawn -= dt;

	if (m_timeTillSpawn <= 0)
	{
		sf::Vector2f position = PhysicsManager::getRandomPosition().toSFMLVector();
		EntityFactory::CreatePowerUp(TYPE, position);
		ResetTimeTillSpawn();
	}
}

void PowerUpGenerator::ResetTimeTillSpawn()
{
	m_timeTillSpawn = rand() % (MAX_SPAWN_TIME - MIN_SPAWN_TIME) + MIN_SPAWN_TIME;
}
