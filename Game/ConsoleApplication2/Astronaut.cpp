#include "stdafx.h"
#include "Astronaut.h"


Astronaut::Astronaut(Rect rect = Rect(), bool isMiniMapObject = false)
	: MovingGameObject(rect, Vector2D(50, 0), isMiniMapObject),
	  m_maxWanderTime(10),
	  m_wanderTimeRemaining(0)
{
	m_sprite = m_bounds.toSFMLRect();
	m_sprite.setPosition(m_bounds.pos.toSFMLVector());
}


void Astronaut::Update(float dt)
{
	m_wanderTimeRemaining -= dt;

	if (m_wanderTimeRemaining <= 0)
	{
		m_wanderTimeRemaining = rand() % (m_maxWanderTime + 1);
		m_direction = AIManager::wander();
	}

	UpdatePosition(dt);
	m_sprite.setPosition(m_bounds.pos.toSFMLVector());
}


void Astronaut::Draw(sf::RenderWindow& w)
{
	w.draw(m_sprite);
}