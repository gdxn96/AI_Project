#include "stdafx.h"
#include "Player.h"


Player::Player()
	: m_acceleration(1),
	  m_maxVelocity(sf::Vector2f(4,0)),
	  m_position(sf::Vector2f(50, 50))
{
	m_sprite = sf::RectangleShape(sf::Vector2f(20, 20));
	m_sprite.setPosition(m_position);
}


Player::~Player()
{
}


void Player::Update(float dt)
{
	updateVelocity(dt);
	move(dt);
}


void Player::Draw(sf::RenderWindow& w)
{
	w.draw(m_sprite);
}



void Player::onKeyDown(KeyDownEvent evt)
{
	switch (evt)
	{
	case EventListener::KeyDownEvent::UP:
		m_direction.y = Constants::UP.y;
		break;
	case EventListener::KeyDownEvent::LEFT:
		m_direction.x = Constants::LEFT.x;
		break;
	case EventListener::KeyDownEvent::DOWN:
		m_direction.y = Constants::DOWN.y;
		break;
	case EventListener::KeyDownEvent::RIGHT:
		m_direction.x = Constants::RIGHT.x;
		break;
	}
}

void Player::onKeyUp(KeyUpEvent evt)
{
	switch (evt)
	{
	case EventListener::KeyUpEvent::UP:
		m_direction.y = 0;
		break;
	case EventListener::KeyUpEvent::LEFT:
		m_direction.x = 0;
		break;
	case EventListener::KeyUpEvent::DOWN:
		m_direction.y = 0;
		break;
	case EventListener::KeyUpEvent::RIGHT:
		m_direction.x = 0;
		break;
	}
}



void Player::move(float dt)
{
	m_position += m_velocity;
}



void Player::updateVelocity(float dt)
{
	float accelerationElapsed = m_acceleration * dt;
	pair<bool, bool> movingInSameDirection = isMovingInSameDirection();
	calculateXVelocity(movingInSameDirection.first, accelerationElapsed);
	calculateYVelocity(movingInSameDirection.second, accelerationElapsed);
}

void Player::calculateXVelocity(bool sameDirection, float acceleration)
{
	if (sameDirection)
	{
		m_velocity.x += m_velocity.x < 0 ? -acceleration : acceleration;			// speed up
	}
	else if (m_direction.x == 0)
	{
		m_velocity.x -= m_velocity.x < 0 ? -acceleration : acceleration;			// slow down
	}
	else
	{
		m_velocity.x = 0;
	}
}

void Player::calculateYVelocity(bool sameDirection, float acceleration)
{
	if (!sameDirection)
	{
		if (m_direction.y == 0)
		{
			m_velocity.y -= m_velocity.y < 0 ? -acceleration : acceleration;		// slow down
		}
		else
		{
			m_velocity.y = m_direction.y * m_maxVelocity.y;
		}
	}
}



pair<bool, bool> Player::isMovingInSameDirection()
{
	pair<bool, bool> result;
	result.first = ((m_direction.x < 0) == (m_velocity.x < 0)) && m_direction.x != 0 && m_velocity.x != 0;
	result.second = ((m_direction.y < 0) == (m_velocity.y < 0)) && m_direction.y != 0 && m_velocity.y != 0;
	return result;
}



// 1. KeyDown && Not Same Dir = Change direction
// 2. KeyDown && Same Dir = Speed up
// 3. Diagonal work