#include "stdafx.h"
#include "Player.h"
#include <iostream>


Player::Player(Rect bounds, Vector2D accel, Vector2D maxSpeed, bool isMiniMapObject = false)
	: MovingGameObject(bounds, accel, maxSpeed, isMiniMapObject),
	  m_facingDirection(sf::Vector2f(1, 0)),
	  m_bulletsPerSecond(10),
	  m_shooting(false)
{
}


Player::~Player()
{
}


void Player::Update(float dt)
{
	if (m_shooting)
	{
		UpdateShootState(dt);
	}
	
	UpdateSpeed(dt);
	UpdateDirection();
	UpdatePosition(dt);

	for (int i = m_bullets.size() - 1; i >= 0; i--)
	{
		if (m_bullets[i]->isAlive())
		{
			m_bullets[i]->Update(dt);
		}
		else
		{
			m_bullets.erase(m_bullets.begin() + i);
		}
	}
}


void Player::Draw(sf::RenderWindow& w)
{
	for (Bullet* bullet : m_bullets)
	{
		bullet->Draw(w);
	}

	w.draw(m_bounds.toSFMLRect());
}



void Player::onGenericEvent(GenericEvent evt)
{
	switch (evt)
	{
	case EventListener::GenericEvent::SHOOT:
		m_shooting = true;
		break;
	case EventListener::GenericEvent::NO_SHOOT:
		m_shooting = false;
		break;
	}
}

void Player::onKeyDown(KeyDownEvent evt)
{
	switch (evt)
	{
	case EventListener::KeyDownEvent::UP:
		m_targetDirection.y = Constants::UP.y;
		break;
	case EventListener::KeyDownEvent::LEFT:
		m_targetDirection.x = Constants::LEFT.x;
		m_facingDirection.x = -1;
		break;
	case EventListener::KeyDownEvent::DOWN:
		m_targetDirection.y = Constants::DOWN.y;
		break;
	case EventListener::KeyDownEvent::RIGHT:
		m_targetDirection.x = Constants::RIGHT.x;
		m_facingDirection.x = 1;
		break;
	}
}

void Player::onKeyUp(KeyUpEvent evt)
{
	switch (evt)
	{
	case EventListener::KeyUpEvent::UP:
		m_targetDirection.y = m_targetDirection.y == Constants::UP.y ? 0 : m_targetDirection.y;
		break;
	case EventListener::KeyUpEvent::LEFT:
		m_targetDirection.x = m_targetDirection.x == Constants::LEFT.x ? 0 : m_targetDirection.x;
		break;
	case EventListener::KeyUpEvent::DOWN:
		m_targetDirection.y = m_targetDirection.y == Constants::DOWN.y ? 0 : m_targetDirection.y;
		break;
	case EventListener::KeyUpEvent::RIGHT:
		m_targetDirection.x = m_targetDirection.x == Constants::RIGHT.x ? 0 : m_targetDirection.x;
		break;
	}
}



void Player::UpdateSpeed(float dt)
{
	if (m_targetDirection.x != 0)
	{
		UpdateXSpeed(dt, 1, m_MAXSPEED.x);
	}
	else if (m_targetDirection.x == 0 && m_direction.x != 0)
	{
		UpdateXSpeed(dt, -1, 0);
	}

	if (m_targetDirection.y != 0)
	{
		m_speed.y = m_MAXSPEED.y;
	}
	else if (m_direction.y != 0)
	{
		UpdateYSpeed(dt, -1, 0);
	}
}



void Player::UpdateDirection()
{
	if (m_speed.x == 0)
	{
		m_direction.x = 0;
	}
	else if (m_targetDirection.x != 0)
	{
		m_direction.x = m_targetDirection.x;
	}

	if (m_speed.y == 0)
	{
		m_direction.y = 0;
	}
	else if (m_targetDirection.y != 0)
	{
		m_direction.y = m_targetDirection.y;
	}
}



void Player::UpdateShootState(float dt)
{
	m_timeTillNextShot -= dt;

	if (m_timeTillNextShot <= 0)
	{
		m_timeTillNextShot = 1.0f / m_bulletsPerSecond;
		m_bullets.push_back(new Bullet(m_bounds.getCentreCopy(), m_facingDirection));
	}
}