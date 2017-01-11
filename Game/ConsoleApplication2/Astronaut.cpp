#include "stdafx.h"
#include "Astronaut.h"


Astronaut::Astronaut(Rect rect = Rect(), bool isMiniMapObject = false)
	: AIGameObject(rect, Vector2D(50, 0), isMiniMapObject),
	  m_maxWanderTime(3),
	  m_wanderTimeRemaining(0)
{
	m_sprite = m_bounds.toSFMLRect();
	m_sprite.setPosition(m_bounds.pos.toSFMLVector());
}


void Astronaut::Update(float dt)
{
	AIManager::wander(dt, m_wanderTimeRemaining, m_maxWanderTime, m_direction, true);
	AIManager::move(dt, m_bounds.pos, m_speed * m_direction);
	m_sprite.setPosition(m_bounds.pos.toSFMLVector());
}


void Astronaut::Draw(sf::RenderWindow& w)
{
	w.draw(m_sprite);
}