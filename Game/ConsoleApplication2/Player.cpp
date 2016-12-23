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
	float accelerationElapsed = m_acceleration * dt;
	updateXSpeed(accelerationElapsed);
	updateYSpeed(accelerationElapsed);
	limitSpeed();
	updateDirection();
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
		m_targetDirection.y = Constants::UP.y;
		break;
	case EventListener::KeyDownEvent::LEFT:
		m_targetDirection.x = Constants::LEFT.x;
		break;
	case EventListener::KeyDownEvent::DOWN:
		m_targetDirection.y = Constants::DOWN.y;
		break;
	case EventListener::KeyDownEvent::RIGHT:
		m_targetDirection.x = Constants::RIGHT.x;
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



void Player::updateXSpeed(float acceleration)
{
	if (m_targetDirection.x != 0)
	{
		m_speed.x += acceleration;
	}
	else if (m_targetDirection.x == 0 && m_direction.x != 0)
	{
		m_speed.x -= acceleration;
	}
}

void Player::updateYSpeed(float acceleration)
{
	if (m_targetDirection.y != 0)
	{
		m_speed.y = m_maxSpeed;
	}
	else if (m_direction.y != 0)
	{
		m_speed.y -= acceleration;
	}
}

void Player::limitSpeed()
{
	if (m_speed.x < 0)
	{
		m_speed.x = 0;
	}
	else if (m_speed.x > m_maxSpeed)
	{
		m_speed.x = m_maxSpeed;
	}

	if (m_speed.y < 0)
	{
		m_speed.y = 0;
	}
	else if (m_speed.y > m_maxSpeed)
	{
		m_speed.y = m_maxSpeed;
	}
}



void Player::updateDirection()
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




void Player::move(float dt)
{
	m_position.x += (m_direction.x * (m_speed.x * dt));
	m_position.y += (m_direction.y * (m_speed.y * dt));
	m_sprite.setPosition(m_position);
}