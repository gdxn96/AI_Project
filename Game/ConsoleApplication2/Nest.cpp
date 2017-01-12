#include "stdafx.h"
#include "Nest.h"

Nest::Nest(Vector2D pos, Vector2D dir, float speed)
:	GameObject(sf::FloatRect(pos.x, pos.y, 40, 40), true),
	m_shape(sf::Vector2f(40,40)),
	m_position(pos),
	m_speed(speed),
	m_direction(dir)
{
	m_shape.setPosition(pos.toSFMLVector());
	m_shape.setFillColor(sf::Color::Yellow);
}

void Nest::Draw(sf::RenderWindow & window)
{
	window.draw(m_shape);
}

void Nest::Update(float dt)
{
	AIManager::wander(dt, m_timeUntilChangeDirection, MAX_TIME, m_direction, false);
	PhysicsManager::move(dt, m_position, m_direction * m_speed);
	PhysicsManager::BindPositionToLevel(m_position, m_direction);

	m_shape.setPosition(m_position.toSFMLVector());
	m_bounds.left = m_position.x;
	m_bounds.top = m_position.y;
}

void Nest::DrawWithXOffset(sf::RenderWindow & window, float xOffset)
{
	m_shape.move(sf::Vector2f(xOffset, 0));
	window.draw(m_shape);
	m_shape.move(sf::Vector2f(-xOffset, 0));
}

void Nest::wrapPositions(Camera & cam)
{
	cam.Wrap(m_position);
	m_shape.setPosition(m_position.toSFMLVector());
}
