#include "stdafx.h"
#include "Player.h"


Player::Player()
	: m_acceleration(Vector2D(1,0)),
	  m_maxVelocity(Vector2D(4,0))
{
}


Player::~Player()
{
}


void Player::Update(float dt)
{
	updateVelocity(dt);
}


void Player::Draw(const sf::RenderWindow& w)
{

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



void Player::updateVelocity(float dt)
{
	m_velocity.x = m_direction.x == 0 ? 0 : calculateXVelocity(dt);
	m_velocity.y = m_direction.y == 0 ? 0 : calculateYVelocity(dt);
}

float Player::calculateXVelocity(float dt)
{
	/*if (m_velocity.x > 0 && m_direction.x > 0)
	{
		return 
	}*/
}

float Player::calculateYVelocity(float dt)
{

}



// 1. KeyDown && Not Same Dir = Change direction
// 2. KeyDown && Same Dir = Speed up
// 3. Diagonal work