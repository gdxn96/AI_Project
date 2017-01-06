#include "stdafx.h"
#include "Astronaut.h"

Astronaut::Astronaut(Rect rectangle = Rect(), bool isMiniMapObject = false)
	: GameObject(rectangle, isMiniMapObject),
	  m_directionChangeTimeMax(10),
	  m_directionChangeTimeRemaining(0),
	  m_speed(50)
{
	m_sprite = sf::RectangleShape(sf::Vector2f(m_bounds.size.x, m_bounds.size.y));
	m_sprite.setPosition(sf::Vector2f(m_bounds.pos.x, m_bounds.pos.y));
}

void Astronaut::Update(float dt)
{
	m_directionChangeTimeRemaining -= dt;

	if (m_directionChangeTimeRemaining <= 0)
	{
		m_directionChangeTimeRemaining = rand() % (m_directionChangeTimeMax + 1);
		m_direction = AIManager::wander();
	}

	move(dt);
}

void Astronaut::Draw(sf::RenderWindow& w)
{
	w.draw(m_sprite);
}


void Astronaut::move(float dt)
{
	sf::Vector2f pos = m_sprite.getPosition();
	pos.x += (m_direction.x * (m_speed * dt));
	m_sprite.setPosition(pos);
}