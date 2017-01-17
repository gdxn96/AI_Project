#include "stdafx.h"
#include "Astronaut.h"


Astronaut::Astronaut(sf::Vector2f position, sf::Vector2f size)
:   GameObject(sf::FloatRect(position, size), true),
    m_beingAbducted(false),
	m_groundY(position.y),
    m_position(position),
	m_size(size),
	m_speed(50, 0),
	m_wanderTimeRemaining(0),
	MAX_WANDER_TIME(3),
	m_currentState(m_states::WANDER),
	m_closestAbductor(nullptr),
	m_evadeDistance(200)
{
	m_shape = sf::RectangleShape(sf::Vector2f(10, 20));
	m_shape.setPosition(m_position.toSFMLVector());
}


void Astronaut::Update(float dt)
{
	UpdateState();

	switch (m_currentState)
	{
	case m_states::WANDER:
		AIManager::wanderHorizontal(dt, m_wanderTimeRemaining, MAX_WANDER_TIME, m_direction);
		UpdatePosition(dt);
		break;
	case m_states::EVADE:
		AIManager::evadeFrom(m_position, m_closestAbductorPosition, m_direction);
		m_direction.y = 0;
		m_direction.x = m_direction.x > 0 ? 1 : -1;
		UpdatePosition(dt);
		break;
	case m_states::FALLING:
		m_position.y += m_speed.x * dt;
		break;
	}
}

void Astronaut::UpdatePosition(float dt)
{
	PhysicsManager::move(dt, m_position, m_speed * m_direction);
	m_shape.setPosition(m_position.toSFMLVector());
	m_bounds.left = m_position.x;
}

void Astronaut::UpdateState()
{
	switch (m_currentState)
	{
	case m_states::WANDER:
		if (m_closestAbductor != nullptr)
		{
			if (Vector2D::Distance(m_position, m_closestAbductorPosition) <= m_evadeDistance)
			{
				m_currentState = m_states::EVADE;
			}
		}
		break;
	case m_states::EVADE:
		if (m_closestAbductor != nullptr)
		{
			if (Vector2D::Distance(m_position, m_closestAbductorPosition) > m_evadeDistance)
			{
				m_currentState = m_states::WANDER;
			}
		}
		break;
	case m_states::FALLING:
		if (m_position.y >= m_groundY)
		{
			m_position.y = m_groundY;
			m_currentState = m_states::WANDER;
		}
		break;
	}
}


void Astronaut::Draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
}

void Astronaut::DrawWithXOffset(sf::RenderWindow & window, float xOffset)
{
	m_shape.move(sf::Vector2f(xOffset, 0));
	window.draw(m_shape);
	m_shape.move(sf::Vector2f(-xOffset, 0));
}

void Astronaut::wrapPositions(Camera & cam)
{
	cam.Wrap(m_position);
	m_shape.setPosition(m_position.toSFMLVector());
}



void Astronaut::fall(float dt)
{
	m_position.y += m_speed.y * dt;

	if (m_position.y > m_groundY)
	{
		m_position.y = m_groundY;
	}
}



Vector2D Astronaut::getPosition()
{
	return m_position;
}

Vector2D Astronaut::getSize()
{
	return m_size;
}

void Astronaut::setBeingAbducted()
{
	m_currentState = m_states::ABDUCTED;
}

void Astronaut::setFalling()
{
	m_currentState = m_states::FALLING;
}

void Astronaut::setClosestAbductor(Abductor * abductor, Vector2D position)
{
	m_closestAbductor = abductor;
	m_closestAbductorPosition = position;
}

void Astronaut::setPosition(Vector2D position)
{
	m_position = position;
}

bool Astronaut::isOnGround()
{
	return m_position.y == m_groundY;
}