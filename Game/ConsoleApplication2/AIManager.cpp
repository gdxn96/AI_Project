#include "stdafx.h"
#include "AIManager.h"
#include <limits.h>



Player* AIManager::m_player = nullptr;
vector<Astronaut*> AIManager::m_astronauts;



void AIManager::registerPlayer(Player* player)
{
	m_player = player;
}

void AIManager::registerAstronaut(Astronaut* astronaut)
{
	m_astronauts.push_back(astronaut);
}



void AIManager::unregisterPlayer()
{
	m_player = nullptr;
}

void AIManager::unregisterAstronaut(Astronaut* astronaut)
{
	std::remove(m_astronauts.begin(), m_astronauts.end(), astronaut);
}



Vector2D AIManager::getPlayerPos()
{
	return m_player->getPosition();
}

Vector2D AIManager::getClosestAstronautPos(Vector2D position)
{
	int index = 0;
	float closestDistance = std::numeric_limits<float>::max();
	
	for (int i = 0; i < m_astronauts.size(); i++)
	{
		Vector2D astronautPosition = m_astronauts[i]->getPosition();
		float newDistance = Vector2D::Distance(position, astronautPosition);

		if (newDistance < closestDistance)
		{
			index = i;
			closestDistance = newDistance;
		}
	}

	if (index < m_astronauts.size())
	{
		return m_astronauts[index]->getPosition();
	}
	else
	{
		return NULL;
	}
}



void AIManager::wander(float dt, float& timeRemaining, int maxTime, Vector2D& direction, bool horizontalOnly)
{
	timeRemaining -= dt;

	if (timeRemaining <= 0)
	{
		timeRemaining = rand() % (maxTime + 1);
		direction.x = rand() & 1 ? 1 : -1;
		direction.y = horizontalOnly ? 0 : (rand() & 1 ? 1 : -1);
	}
}

void AIManager::seekToward(Vector2D position, Vector2D targetPosition, Vector2D& direction)
{
	direction = targetPosition - position;
	direction.Normalize();
}

void AIManager::evadeFrom(Vector2D position, Vector2D targetPosition, Vector2D& direction)
{
	direction = position - targetPosition;
	direction.Normalize();
}

void AIManager::flock()
{

}