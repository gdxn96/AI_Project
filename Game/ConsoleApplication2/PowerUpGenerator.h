#pragma once

#include "EntityFactory.h"
#include "PowerUpTypes.h"
#include "AIManager.h"


class PowerUpGenerator
{
public:
	PowerUpGenerator(int minSpawnTime, int maxSpawnTime);
	~PowerUpGenerator();
	virtual void Update(float dt) = 0;

protected:
	const int MIN_SPAWN_TIME;
	const int MAX_SPAWN_TIME;
	float m_timeTillSpawn;

	void ResetTimeTillSpawn();
};

