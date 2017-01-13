#pragma once

#include "Vector2D.h"
#include "GameObject.h"
#include "Boid.h"

class AIManager
{
public:
	static void wander(float dt, float& timeRemaining, int maxTime, Vector2D& direction, bool horizontalOnly);
	static void seekToward(float dt, Vector2D& position, Vector2D targetPosition);
	static void evade();

	static Vector2D Separation(std::vector<Boid*> flockObjects, Vector2D & position, Vector2D & velocity, const float maxSpeed, const float maxAcceleration, bool predator = false);
	static Vector2D Alignment(std::vector<Boid*> flockObjects, Vector2D & position, Vector2D & velocity, const float maxSpeed, const float maxAcceleration);
	static Vector2D Cohesion(std::vector<Boid*> flockObjects, Vector2D & position, Vector2D & velocity, Vector2D & acceleration, const float maxSpeed, const float maxAcceleration);
	static Vector2D seek(Vector2D target, Vector2D & velocity, Vector2D & acceleration, const float maxSpeed, const float maxAcceleration);
	static void flock(std::vector<Boid*> v, Vector2D & acceleration, Vector2D & position, Vector2D & velocity, const float maxSpeed, const float maxAcceleration, bool predator = false);
	static void swarm(std::vector<Boid*> v, Vector2D & position, Vector2D & acceleration);
};