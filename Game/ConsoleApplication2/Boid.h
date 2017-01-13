#pragma once

class Boid
{
public:
	virtual Vector2D getPosition() = 0;
	virtual Vector2D getVelocity() = 0;
	virtual bool isPredator() = 0;
};
