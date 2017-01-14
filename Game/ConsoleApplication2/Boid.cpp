#include "stdafx.h"
#include "Boid.h"
#include "AIManager.h"

Boid::Boid(bool flocks)
{
	if (flocks)
	{
		AIManager::registerFlockBoid(this);
	}
	else
	{
		AIManager::registerSwarmBoid(this);
	}
}

Boid::~Boid()
{
	AIManager::unregisterBoid(this);
}
