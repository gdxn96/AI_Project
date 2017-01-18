#include "stdafx.h"
#include "FireRatePowerupGenerator.h"


FireRatePowerupGenerator::FireRatePowerupGenerator(int minSpawnTime, int maxSpawnTime)
	: PowerUpGenerator(minSpawnTime, maxSpawnTime)
{
}


FireRatePowerupGenerator::~FireRatePowerupGenerator()
{
}

void FireRatePowerupGenerator::Update(float dt)
{
	m_timeTillSpawn -= dt;

	if (m_timeTillSpawn <= 0)
	{
		sf::Vector2f position = AIManager::getRandomPosition().toSFMLVector();
		EntityFactory::CreatePowerUp(PowerUpTypes::MORE_FIRE_RATE, position);
		ResetTimeTillSpawn();
	}
}
