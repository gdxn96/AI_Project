#include "stdafx.h"
#include "Abductor.h"



Abductor::Abductor(sf::Vector2f position, sf::Vector2f size, float minPatrolHeight, float maxPatrolHeight)
	: GameObject(sf::FloatRect(position, size), true),
	  Boid(true),
	  m_patrolArea(0, maxPatrolHeight, 0, minPatrolHeight - maxPatrolHeight),
	  m_position(position),
	  m_seekDistance(400),
	  m_size(size),
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

Abductor::~Abductor() 
{
	if (m_closestAstronaut != nullptr)
	{
		dropAstronaut();
	}
	AIManager::unregisterBoid(this);
	EntityFactory::abductorDeathNotify();
}



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
		calculateAbductPosition();
		AIManager::flock(this, Vector2D(), m_position, m_velocity, 200, 0);
		break;
	case m_states::PATROL_EXIT:
		m_direction.y *= -1;
		break;
	case m_states::SEEK:
		calculateAbductPosition();
		AIManager::seekToward(m_position, m_abductPosition, m_direction);
		break;
	case m_states::ABDUCT:
		AIManager::seekToward(m_position, Vector2D(m_position.x, 0), m_direction);
		m_closestAstronaut->setPosition(Vector2D(m_closestAstronautPosition.x, m_position.y + m_size.h));
		break;
	case m_states::TRANSFORM:
		EntityFactory::CreateMutant(m_position);
		m_closestAstronaut->kill();
		kill();
		break;
	}

	m_velocity = m_direction * m_speed;
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
		if (shouldAbductAstronaut())
		{
			m_currentState = m_states::ABDUCT;
			cout << "Abducting Astronaut" << endl;
		}
		break;
	case m_states::ABDUCT:
		if (m_position.y <= 0)
		{
			m_currentState = m_states::TRANSFORM;
			cout << "Transforming" << endl;
		}
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



void Abductor::calculateAbductPosition()
{
	if (m_closestAstronaut != nullptr)
	{
		Vector2D sizeDiff = m_size - m_closestAstronaut->getSize();
		float abductPositionX = m_closestAstronautPosition.x - sizeDiff.w / 2;
		float abductPositionY = m_closestAstronautPosition.y - m_size.h;
		m_abductPosition = Vector2D(abductPositionX, abductPositionY);
	}
}



bool Abductor::isInPatrolArea()
{
	return m_position.y >= m_patrolArea.top && m_position.y <= m_patrolArea.top + m_patrolArea.height;
}

bool Abductor::shouldSeekAstronaut()
{
	bool result = false;

	if (m_closestAstronaut != nullptr)
	{
		float distanceFromAstronaut = Vector2D::Distance(m_position, m_closestAstronautPosition);
		result = distanceFromAstronaut <= m_seekDistance;
	}
	
	return result;
}

bool Abductor::shouldAbductAstronaut()
{
	float distanceFromAbductPosition = Vector2D::Distance(m_position, m_abductPosition);
	return (distanceFromAbductPosition <= 0.5f);
}


void Abductor::wrapPositions(Camera& cam)
{
	cam.Wrap(m_position);
	m_shape.setPosition(m_position.toSFMLVector());
	m_bounds.left = m_position.x;
}

void Abductor::dropAstronaut()
{
	m_closestAstronaut->setBeingAbducted(false);
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

bool Abductor::isAbducting()
{
	return m_currentState == m_states::ABDUCT;
}

bool Abductor::isPredator()
{
	return false;
}

bool Abductor::shouldTransform()
{
	return m_currentState == m_states::TRANSFORM;
}