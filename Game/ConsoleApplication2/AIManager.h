#pragma once

#include "Vector2D.h"


class AIManager
{
public:
	static void move(float dt, Vector2D& position, Vector2D& velocity);
	static void accelerate(float dt, Vector2D& speed, Vector2D acceleration, Vector2D targetSpeed);
	static void wander(float dt, float& timeRemaining, int maxTime, Vector2D& direction, bool horizontalOnly);
	static void seek();
	static void evade();
	static void flock();
};