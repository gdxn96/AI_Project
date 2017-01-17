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
	MAX_WANDER_TIME(3)
{
	m_shape = sf::RectangleShape(sf::Vector2f(10, 20));
	m_shape.setPosition(m_position.toSFMLVector());
}


void Astronaut::Update(float dt)
{
	if (!m_beingAbducted)
	{
		if (isOnGround())
		{
			AIManager::wander(dt, m_wanderTimeRemaining, MAX_WANDER_TIME, m_direction, true);
			PhysicsManager::move(dt, m_position, m_speed * m_direction);
			m_shape.setPosition(m_position.toSFMLVector());
			m_bounds.left = m_position.x;
		}
		else
		{
			fall(dt);
		}
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

void Astronaut::setBeingAbducted(bool value)
{
	m_beingAbducted = value;
}

void Astronaut::setPosition(Vector2D position)
{
	m_position = position;
}

bool Astronaut::isOnGround()
{
	return m_position.y == m_groundY;
}