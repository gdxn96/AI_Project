#pragma once

#include "EntityFactory.h"
#include "PowerUpTypes.h"
#include "PhysicsManager.h"


class PowerUpGenerator
{
public:
	PowerUpGenerator(int powerupType, int minSpawnTime, int maxSpawnTime);
	~PowerUpGenerator();
	void Update(float dt);

private:
	const int MIN_SPAWN_TIME;
	const int MAX_SPAWN_TIME;
	float m_timeTillSpawn;
	const int TYPE;

	void ResetTimeTillSpawn();
};

