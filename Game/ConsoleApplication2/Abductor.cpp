#include "stdafx.h"
#include "Abductor.h"



Abductor::Abductor(sf::Vector2f position, sf::Vector2f size, float minPatrolHeight, float maxPatrolHeight)
	: GameObject(sf::FloatRect(position, size), true),
	  Boid(true),
	  m_patrolArea(0, maxPatrolHeight, 0, maxPatrolHeight - minPatrolHeight),
	  m_position(position),
	  m_seekDistance(400),
	  m_abductDistance(100),
	  m_shape(size),
	  m_speed(300, 200),
	  MAX_WANDER_TIME(10),
	  m_wanderTimeRemaining(0)
{
	m_currentState = m_states::TOSURFACE;
	m_shape.setPosition(m_position.toSFMLVector());
	sf::Color darkGreen = sf::Color(76, 153, 0, 255);
	m_shape.setFillColor(darkGreen);
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
	case m_states::PATROL_EXIT:
		m_direction.y *= -1;
		break;
	case m_states::SEEK:
		AIManager::seekToward(m_position, m_closestAstronautPosition, m_direction);
		break;
	case m_states::ABDUCT:
		break;
	}

	m_velocity = m_direction * m_speed;
	AIManager::flock(this, Vector2D(), m_position, m_velocity, 200, 0);
	PhysicsManager::move(dt, m_position, m_velocity);
}

void Abductor::UpdateState()
{
	switch (m_currentState)
	{
	case m_states::TOSURFACE:
		if (isInPatrolArea())
		{
			m_currentState = m_states::PATROL;
			cout << "Patrolling" << endl;
		}
		break;
	case m_states::PATROL:
		if (!isInPatrolArea())
		{
			m_currentState = m_states::PATROL_EXIT;
			cout << "Leaving Patrol Area" << endl;
		}
		else if (shouldSeekAstronaut())
		{
			m_currentState = m_states::SEEK;
			cout << "Seeking Astronaut" << endl;
		}
		break;
	case m_states::PATROL_EXIT:
		if (isInPatrolArea())
		{
			m_currentState = m_states::PATROL;
			cout << "Patrolling" << endl;
		}
	case m_states::SEEK:
		/*if (shouldAbductAstronaut())
		{
			m_currentState = m_states::ABDUCT;
			cout << "Abducting Astronaut" << endl;
		}*/
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
	float distanceFromAstronaut = Vector2D::Distance(m_position, m_closestAstronautPosition);
	return distanceFromAstronaut <= m_seekDistance;
}

bool Abductor::shouldAbductAstronaut()
{
	float distanceFromAstronaut = Vector2D::Distance(m_position, m_closestAstronautPosition);
	return distanceFromAstronaut <= m_abductDistance;
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
	return m_velocity;
}

bool Abductor::isPredator()
{
	return false;
}
