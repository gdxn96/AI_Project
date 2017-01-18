#pragma once

#include <vector>
#include "HyperJumpGenerator.h"

using namespace std;


class PowerUpManager
{
public:
	PowerUpManager();
	~PowerUpManager();
	void AddPowerUpGenerator(PowerUpGenerator* powerUpGenerator);
	void Update(float dt);

private:
	vector<PowerUpGenerator*> m_generators;
};

