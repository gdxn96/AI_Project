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
	  m_speed(150, 250),
	  MAX_WANDER_TIME(10),
	  m_wanderTimeRemaining(0),
	  FIRE_RANGE(400),
	  FIRE_RATE(1),
      m_timeTillFire(0.1f),
	  MAX_EMP_TIME(5),
	  m_timetillEMPEnds(0)
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
	if (isUnderEMP())
	{
		m_timetillEMPEnds -= dt;
		PhysicsManager::move(dt, m_position, m_velocity);

		if (m_position.y >= m_groundY)
		{
			m_position.y = m_groundY;
		}
	}
	else
	{
		UpdateState();
		UpdateShooting(dt);

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
			//m_direction.y *= -1;
			AIManager::seekToward(m_position, Vector2D(m_position.x, m_patrolArea.top), m_direction);
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

	m_shape.setPosition(m_position.toSFMLVector());
	m_bounds.left = m_position.x;
	m_bounds.top = m_position.y;
}

void Abductor::UpdateShooting(float dt)
{
	if (m_timeTillFire > 0)
	{
		m_timeTillFire -= dt;

		if (m_timeTillFire <= 0)
		{
			Vector2D playerPos = AIManager::getPlayerPos();

			if (Vector2D::Distance(m_position, playerPos) < FIRE_RANGE)
			{
				m_timeTillFire = FIRE_RATE;
				EntityFactory::CreateBullet(m_position, (playerPos - m_position).Normalize(), true);
			}
		}
	}
}

void Abductor::UpdateState()
{
	switch (m_currentState)
	{
	case m_states::TOSURFACE:
		if (isInPatrolArea())
		{
			m_currentState = m_states::PATROL;
		}
		break;
	case m_states::PATROL:
		if (!isInPatrolArea())
		{
			m_currentState = m_states::PATROL_EXIT;
		}
		else if (shouldSeekAstronaut())
		{
			m_currentState = m_states::SEEK;
		}
		break;
	case m_states::PATROL_EXIT:
		if (isInPatrolArea())
		{
			m_currentState = m_states::PATROL;
		}
	case m_states::SEEK:
		if (shouldAbductAstronaut())
		{
			m_currentState = m_states::ABDUCT;
			m_closestAstronaut->setBeingAbducted();
		}
		break;
	case m_states::ABDUCT:
		if (m_position.y <= 0)
		{
			m_currentState = m_states::TRANSFORM;
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
	return (distanceFromAbductPosition <= 1);
}


void Abductor::wrapPositions(Camera& cam)
{
	cam.Wrap(m_position);
	m_shape.setPosition(m_position.toSFMLVector());
	m_bounds.left = m_position.x;
	m_bounds.top = m_position.y;
}

void Abductor::dropAstronaut()
{
	m_closestAstronaut->setFalling();
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

bool Abductor::isPatrolling()
{
	return m_currentState == m_states::PATROL;
}

bool Abductor::isPredator()
{
	return false;
}

bool Abductor::shouldTransform()
{
	return m_currentState == m_states::TRANSFORM;
}

void Abductor::destroyElectrics()
{
	m_velocity = Vector2D::DOWN;
	m_velocity = m_velocity * m_speed;
	m_timetillEMPEnds = MAX_EMP_TIME;

	if (m_currentState == m_states::ABDUCT)
	{
		dropAstronaut();
		m_currentState = m_states::TOSURFACE;
	}
}

void Abductor::setGroundY(float y)
{
	m_groundY = y;
}

bool Abductor::isUnderEMP()
{
	return m_timetillEMPEnds > 0;
}