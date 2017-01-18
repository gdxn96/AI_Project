#include "stdafx.h"
#include "PowerUpManager.h"


PowerUpManager::PowerUpManager()
{
}


PowerUpManager::~PowerUpManager()
{
}


void PowerUpManager::AddPowerUpGenerator(PowerUpGenerator* powerUpGenerator)
{
	m_generators.push_back(powerUpGenerator);
}


void PowerUpManager::Update(float dt)
{
	int generatorCount = m_generators.size();

	for (int i = 0; i < generatorCount; i++)
	{
		m_generators[i]->Update(dt);
	}
}