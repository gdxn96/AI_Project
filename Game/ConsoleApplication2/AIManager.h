#pragma once

#include "Vector2D.h"


class AIManager
{
public:
	static void wander(float dt, float& timeRemaining, int maxTime, Vector2D& direction, bool horizontalOnly);
	static void seekToward(float dt, Vector2D& position, Vector2D targetPosition);
	static void evade();
	static void flock();
};