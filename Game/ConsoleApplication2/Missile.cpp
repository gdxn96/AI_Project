#include "stdafx.h"
#include "Missile.h"
#include "AIManager.h"

Missile::Missile(Vector2D pos)
	: GameObject(sf::FloatRect(pos.x, pos.y, 20, 10)),
	m_position(pos),
	m_velocity((0,0)),
	m_acceleration((0,0)),
	m_timeToLive(10),
	m_shape(sf::Vector2f(20, 10)),
	MAX_SPEED(800)
{
	m_shape.setPosition(m_position.toSFMLVector());
	m_bounds.left = m_position.x;
	m_bounds.top = m_position.y;
	m_shape.setFillColor(sf::Color::Red);
}

void Missile::Update(float dt)
{
	Vector2D dir(0,0);
	Vector2D playerPos = AIManager::getClosestPlayerPos(m_position);
	AIManager::seekToward(m_position, playerPos, dir);
	m_velocity = dir * MAX_SPEED;
	AIManager::seek(dir, m_velocity, m_acceleration, MAX_SPEED, MAX_SPEED * 50);
	PhysicsManager::accelerateVelocity(dt, m_velocity, m_acceleration, MAX_SPEED);
	PhysicsManager::move(dt, m_position, m_velocity);

	if (m_timeToLive > 0)
	{
		m_timeToLive -= dt;
	}
	else
	{
		kill();
	}

	m_shape.setPosition(m_position.toSFMLVector());
	m_bounds.left = m_position.x;
	m_bounds.top = m_position.y;
}

void Missile::wrapPositions(Camera & cam)
{
	cam.Wrap(m_position);
	m_shape.setPosition(m_position.toSFMLVector());
}

void Missile::Draw(sf::RenderWindow& w)
{
	w.draw(m_shape);
}

void Missile ::DrawWithXOffset(sf::RenderWindow & window, float xOffset)
{
	m_shape.move(sf::Vector2f(xOffset, 0));
	window.draw(m_shape);
	m_shape.move(sf::Vector2f(-xOffset, 0));
}