#pragma once

#include "PowerUpGenerator.h"


class HyperJumpGenerator : public PowerUpGenerator
{
public:
	HyperJumpGenerator(int minSpawnTime, int maxSpawnTime);
	~HyperJumpGenerator();
	void Update(float dt) override;
};

