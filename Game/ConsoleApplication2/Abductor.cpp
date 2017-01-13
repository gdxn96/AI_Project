#include "stdafx.h"
#include "Abductor.h"



Abductor::Abductor(sf::Vector2f position, sf::Vector2f size, float minPatrolHeight, float maxPatrolHeight)
	: GameObject(sf::FloatRect(position, size), true),
	  m_patrolArea(0, maxPatrolHeight, 0, minPatrolHeight),
	  m_position(position),
	  m_seekDistance(400),
	  m_shape(size),
	  m_speed(50, 50),
	  MAX_WANDER_TIME(10),
	  m_wanderTimeRemaining(0)
{
	m_shape.setPosition(m_position.toSFMLVector());
}

Abductor::~Abductor() { }



void Abductor::Update(float dt)
{
	if (isInPatrolArea())
	{
		Vector2D astronautPosition = AIManager::getClosestAstronautPos(m_position);
		float distanceFromAstronaut = Vector2D::Distance(m_position, astronautPosition);

		if (distanceFromAstronaut < m_seekDistance)
		{
			AIManager::seekToward(m_position, astronautPosition, m_direction);
		}
		else
		{
			AIManager::wander(dt, m_wanderTimeRemaining, MAX_WANDER_TIME, m_direction);
		}
	}
	else
	{
		AIManager::seekToward(m_position, Vector2D(m_position.x, m_patrolArea.top), m_direction);
	}

	PhysicsManager::move(dt, m_position, m_direction * m_speed);
}

void Abductor::Draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
}

void Abductor::DrawWithXOffset(sf::RenderWindow& window, float xOffset)
{
	m_shape.move(sf::Vector2f(xOffset, 0));
	window.draw(m_shape);
	m_shape.move(sf::Vector2f(-xOffset, 0));
}



bool Abductor::isInPatrolArea()
{
	return m_position.y >= m_patrolArea.top && m_position.y <= m_patrolArea.top + m_patrolArea.height;
}


void Abductor::wrapPositions(Camera& cam)
{
	cam.Wrap(m_position);
	m_shape.setPosition(m_position.toSFMLVector());
}