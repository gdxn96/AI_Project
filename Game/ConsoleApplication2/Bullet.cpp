#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet(Vector2D pos, Vector2D dir)
	: MovingGameObject(Rect(pos, Vector2D(10, 5)), Vector2D(1200, 0)),
	  m_timeToLive(1)
{
	m_direction = dir;
}

Bullet::~Bullet() { }


void Bullet::Update(float dt)
{
	UpdatePosition(dt);

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