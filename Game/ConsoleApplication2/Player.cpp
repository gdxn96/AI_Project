#include "stdafx.h"
#include "Player.h"
#include <iostream>


Player::Player()
	: m_acceleration(800),
	  m_maxSpeed(400),
	  m_position(sf::Vector2f(950, 530))
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
		m_direction.y = m_direction.y == Constants::UP.y ? 0 : m_direction.y;
		break;
	case EventListener::KeyUpEvent::LEFT:
		m_direction.x = m_direction.x == Constants::LEFT.x ? 0 : m_direction.x;
		break;
	case EventListener::KeyUpEvent::DOWN:
		m_direction.y = m_direction.y == Constants::DOWN.y ? 0 : m_direction.y;
		break;
	case EventListener::KeyUpEvent::RIGHT:
		m_direction.x = m_direction.x == Constants::RIGHT.x ? 0 : m_direction.x;
		break;
	}
}



void Player::move(float dt)
{
	if (m_direction.y != 0)
	{
		int debug = 0;
	}

	m_position += (m_velocity * dt);
	m_sprite.setPosition(m_position);
}



void Player::updateVelocity(float dt)
{
	float accelerationElapsed = m_acceleration * dt;
	pair<bool, bool> mustMove = shouldMove();

	if (mustMove.first)
	{
		calculateXVelocity(accelerationElapsed);
	}
	
	if (mustMove.second)
	{
		calculateYVelocity(accelerationElapsed);
	}
}

void Player::calculateXVelocity(float acceleration)
{
	float speed = abs(m_velocity.x);
	bool sameDirection = isSameDirection(m_direction.x, m_velocity.x);

	// If going in same direction AND not at max speed...
	if ((sameDirection || m_velocity.x == 0) && (speed != m_maxSpeed))
	{
		// increase speed
		speed += acceleration;
		
		if (speed > m_maxSpeed)
		{
			speed = m_maxSpeed;
		}
	}
	else if (m_direction.x == 0)
	{
		// decrease speed
		speed -= acceleration;

		if (speed < 0)
		{
			speed = 0;
		}
	}

	m_velocity.x = (m_direction.x * speed);
}

void Player::calculateYVelocity(float acceleration)
{
	float speed = abs(m_velocity.y);

	if (m_direction.y == 0)
	{
		// decrease speed
		speed -= acceleration;

		if (speed < 0)
		{
			speed = 0;
		}
	}
	else
	{
		speed = m_maxSpeed;
	}

	m_velocity.y = m_direction.y * speed;
}



bool Player::isSameDirection(float direction, float velocity)
{
	return ((direction < 0) == (velocity < 0));
}

pair<bool, bool> Player::shouldMove()
{
	pair<bool, bool> result;
	result.first = !(m_direction.x == 0 && m_velocity.x == 0);
	result.second = !(m_direction.y == 0 && m_velocity.y == 0);
	return result;
}



// 1. KeyDown && Not Same Dir = Change direction
// 2. KeyDown && Same Dir = Speed up
// 3. Diagonal work
// 4. KeyUp = Slow down