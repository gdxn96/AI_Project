#pragma once

#include "Vector2D.h"


class AIManager
{
public:
	static void wander(float dt, float& timeRemaining, int maxTime, Vector2D& direction, bool horizontalOnly);
	static void seek();
	static void evade();
	static void flock();
};