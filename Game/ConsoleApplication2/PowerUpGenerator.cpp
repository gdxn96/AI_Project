#include "stdafx.h"
#include "PowerUpGenerator.h"


PowerUpGenerator::PowerUpGenerator(int minSpawnTime, int maxSpawnTime)
	: MIN_SPAWN_TIME(minSpawnTime),
	  MAX_SPAWN_TIME(maxSpawnTime)
{
	ResetTimeTillSpawn();
}


PowerUpGenerator::~PowerUpGenerator()
{
}

void PowerUpGenerator::ResetTimeTillSpawn()
{
	m_timeTillSpawn = rand() % (MAX_SPAWN_TIME - MIN_SPAWN_TIME) + MIN_SPAWN_TIME;
}
