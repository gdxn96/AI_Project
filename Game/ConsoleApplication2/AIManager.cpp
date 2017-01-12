#include "stdafx.h"
#include "AIManager.h"

void AIManager::wander(float dt, float& timeRemaining, int maxTime, Vector2D& direction, bool horizontalOnly = false)
{
	timeRemaining -= dt;

	if (timeRemaining <= 0)
	{
		timeRemaining = rand() % (maxTime + 1);
		direction.x = rand() & 1 ? 1 : -1;
		direction.y = horizontalOnly ? 0 : (rand() & 1 ? 1 : -1);
	}
}

void AIManager::seek()
{

}

void AIManager::evade()
{

}

void AIManager::flock()
{

}