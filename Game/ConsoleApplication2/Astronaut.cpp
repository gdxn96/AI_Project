#include "stdafx.h"
#include "Astronaut.h"


Astronaut::Astronaut(Vector2D position, bool isMiniMapObject = false)
: 
	AIGameObject(sf::FloatRect(position.x, position.y, 10, 20), Vector2D(50, 0), isMiniMapObject),
	m_maxWanderTime(3),
	m_wanderTimeRemaining(0),
	m_position(position)
{
	m_shape = sf::RectangleShape(sf::Vector2f(10, 20));
	m_shape.setPosition(m_position.toSFMLVector());
}


void Astronaut::Update(float dt)
{
	AIManager::wander(dt, m_wanderTimeRemaining, m_maxWanderTime, m_direction, true);
	PhysicsManager::move(dt, m_position, m_speed * m_direction);
	m_shape.setPosition(m_position.toSFMLVector());
}


void Astronaut::Draw(sf::RenderWindow& w)
{
	w.draw(m_shape);
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
