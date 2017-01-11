#include "stdafx.h"
#include "Bullet.h"
#include "AIManager.h"


Bullet::Bullet(Vector2D pos, Vector2D dir)
	: GameObject(Rect(pos, Vector2D(10, 5))),
	  m_velocity(Vector2D(1200, 0) * dir),
	  m_timeToLive(1)
{
}

Bullet::~Bullet() { }


void Bullet::Update(float dt)
{
	AIManager::move(dt, m_bounds.pos, m_velocity);

	if (m_timeToLive > 0)
	{
		m_timeToLive -= dt;
	}
}

void Bullet::Draw(sf::RenderWindow& w)
{
	w.draw(m_bounds.toSFMLRect());
}

bool Bullet::isAlive()
{
	return m_timeToLive > 0;
}