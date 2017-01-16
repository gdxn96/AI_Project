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
	m_currentState = m_states::TOSURFACE;
	m_shape.setPosition(m_position.toSFMLVector());
	m_bounds.left = m_position.x;
}

Abductor::~Abductor() { }



void Abductor::Update(float dt)
{
	UpdateState();

	switch (m_currentState)
	{
	case m_states::TOSURFACE:
		AIManager::seekToward(m_position, Vector2D(m_position.x, m_patrolArea.top), m_direction);
		break;
	case m_states::PATROL:
		AIManager::wander(dt, m_wanderTimeRemaining, MAX_WANDER_TIME, m_direction);
		break;
	case m_states::SEEK:
		AIManager::seekToward(m_position, m_closestAstronautPos, m_direction);
		break;
	case m_states::ABDUCT:

		break;
	}

	PhysicsManager::move(dt, m_position, m_direction * m_speed);
}

void Abductor::UpdateState()
{
	switch (m_currentState)
	{
	case m_states::TOSURFACE:
		m_currentState = isInPatrolArea() ? m_states::PATROL : m_currentState;
		break;
	case m_states::PATROL:
		m_currentState = !isInPatrolArea() ? m_states::TOSURFACE : 
						 shouldSeekAstronaut() ? m_states::SEEK : m_currentState;
		break;
	case m_states::SEEK:
		m_currentState = shouldAbductAstronaut() ? m_states::ABDUCT : m_currentState;
		break;
	}
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

bool Abductor::shouldSeekAstronaut()
{
	m_closestAstronautPos = AIManager::getClosestAstronautPos(m_position);
	float distanceFromAstronaut = Vector2D::Distance(m_position, m_closestAstronautPos);
	return (distanceFromAstronaut <= m_seekDistance);
}

bool Abductor::shouldAbductAstronaut()
{
	m_closestAstronautPos = AIManager::getClosestAstronautPos(m_position);
	float distanceFromAstronaut = Vector2D::Distance(m_position, m_closestAstronautPos);
	return (distanceFromAstronaut <= m_abductDistance);
}


void Abductor::wrapPositions(Camera& cam)
{
	cam.Wrap(m_position);
	m_shape.setPosition(m_position.toSFMLVector());
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
