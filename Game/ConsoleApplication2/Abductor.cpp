#include "stdafx.h"
#include "Abductor.h"



Abductor::Abductor(sf::Vector2f position, sf::Vector2f size, float minPatrolHeight, float maxPatrolHeight)
	: GameObject(sf::FloatRect(position, size), true),
	  Boid(true),
	  m_patrolArea(0, maxPatrolHeight, 0, minPatrolHeight),
	  m_position(position),
	  m_seekDistance(400),
	  m_shape(size),
	  m_speed(300, 200),
	  MAX_WANDER_TIME(10),
	  m_wanderTimeRemaining(0)
{
	m_shape.setPosition(m_position.toSFMLVector());
	m_bounds.left = m_position.x;
}

Abductor::~Abductor() { }



void Abductor::Update(float dt)
{
	if (isInPatrolArea())
	{
		float distanceFromAstronaut = m_seekDistance + 1; //default more than seek distance
		Vector2D astronautPosition;

		if (m_closestAstronaut != nullptr)
		{
			astronautPosition = m_closestAstronaut->getPosition();
			distanceFromAstronaut = Vector2D::Distance(m_position, astronautPosition);
		}

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

	m_velocity = m_direction * m_speed;
	Vector2D a;
	AIManager::flock(this, a, m_position, m_velocity, 8000, 8000);
	PhysicsManager::accelerate(dt, m_velocity, a, Vector2D(8000, 8000));
	
	PhysicsManager::move(dt, m_position, m_velocity);
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
	m_bounds.left = m_position.x;
}

void Abductor::setClosestAstronaut(Vector2D position, Astronaut * a)
{
	m_closestAstronautPosition = position;
	m_closestAstronaut = a;
}

Vector2D Abductor::getPosition()
{
	return m_position;
}

Vector2D Abductor::getVelocity()
{
	return m_direction * m_speed;
}

bool Abductor::isPredator()
{
	return false;
}
