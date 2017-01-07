#include "stdafx.h"
#include "Bullet.h"


Bullet::Bullet() {};

Bullet::Bullet(sf::Vector2f pos, sf::Vector2f dir) 
	: MovingGameObject(pos, sf::Vector2f(10, 5), sf::Vector2f(1200, 0)),
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
	w.draw(m_bounds);
}

bool Bullet::isAlive()
{
	return m_timeToLive > 0;
}