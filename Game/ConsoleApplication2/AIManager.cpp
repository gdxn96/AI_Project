#include "stdafx.h"
#include "AIManager.h"



void AIManager::move(float dt, Vector2D& position, Vector2D& velocity)
{
	position += (velocity * dt);
}

void AIManager::accelerate(float dt, Vector2D& speed, Vector2D acceleration, Vector2D targetSpeed)
{
	Vector2D speedChange = acceleration * dt;
	speed += speedChange;
	speed.x = abs(speed.x - targetSpeed.x) <= abs(speedChange.x) * 2 ? targetSpeed.x : speed.x;
	speed.y = abs(speed.y - targetSpeed.y) <= abs(speedChange.y) * 2 ? targetSpeed.y : speed.y;
}

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