#include "stdafx.h"
#include "HyperJumpGenerator.h"


HyperJumpGenerator::HyperJumpGenerator(int minSpawnTime, int maxSpawnTime)
	: PowerUpGenerator(minSpawnTime, maxSpawnTime)
{
}


HyperJumpGenerator::~HyperJumpGenerator()
{
}


void HyperJumpGenerator::Update(float dt)
{
	m_timeTillSpawn -= dt;

	if (m_timeTillSpawn <= 0)
	{
		sf::Vector2f position = AIManager::getRandomPosition().toSFMLVector();
		EntityFactory::CreatePowerUp(PowerUpTypes::HYPERJUMP, position);
		ResetTimeTillSpawn();
	}
}