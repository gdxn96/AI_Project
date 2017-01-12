#include "stdafx.h"
#include "Bullet.h"
#include "AIManager.h"


Bullet::Bullet(Vector2D pos, Vector2D dir)
:	GameObject(false, sf::FloatRect(pos.x, pos.y, 10, 5)),
	m_velocity(Vector2D(1200, 0) * dir),
	m_position(pos),
	m_timeToLive(1),
	m_shape(sf::Vector2f(10,5))
{
	m_shape.setPosition(m_position.toSFMLVector());
}

Bullet::~Bullet() { }


void Bullet::Update(float dt)
{
	AIManager::move(dt, m_position, m_velocity);

	if (m_timeToLive > 0)
	{
		m_timeToLive -= dt;
	}

	m_shape.setPosition(m_position.toSFMLVector());
}

void Bullet::Draw(sf::RenderWindow& w)
{
	w.draw(m_shape);
}

void Bullet::DrawWithXOffset(sf::RenderWindow & window, float xOffset)
{
	m_shape.move(sf::Vector2f(xOffset, 0));
	window.draw(m_shape);
	m_shape.move(sf::Vector2f(-xOffset, 0));
}

bool Bullet::isAlive()
{
	return m_timeToLive > 0;
}