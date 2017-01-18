#pragma once

#include "PowerUpGenerator.h"


class FireRatePowerupGenerator : public PowerUpGenerator
{
public:
	FireRatePowerupGenerator(int minSpawnTime, int maxSpawnTime);
	~FireRatePowerupGenerator();
	void Update(float dt) override;
};

