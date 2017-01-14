#pragma once
#include "Vector2D.h"

//this works, assuming you have neccesary variables to call AIManager::flock & 
//AIManager::swarm and override the pure virtual functions in this class, 
//you still need to call flock and swarm in your object update
class Boid
{
public:
	Boid(bool flocks);
	virtual Vector2D getPosition() = 0;
	virtual Vector2D getVelocity() = 0;
	virtual bool isPredator() = 0;
	~Boid();
};
