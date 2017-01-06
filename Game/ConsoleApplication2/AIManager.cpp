#include "stdafx.h"
#include "AIManager.h"

//AIManager* AIManager::m_instance = 0;
//AIManager::AIManager() { };
//AIManager::~AIManager() { };

Vector2D AIManager::wander()
{
	// Astronaut only wanders, so fixed to horizontal axis
	bool moveRight = (bool)(rand() % 2);
	int xMove = moveRight ? 1 : -1;
	return Vector2D(xMove, 0);
}