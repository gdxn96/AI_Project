#include "stdafx.h"
#include "Mutant.h"
#include "PhysicsManager.h"
#include "AIManager.h"
#include "EntityFactory.h"

Mutant::Mutant(Vector2D pos) :
	Boid(false),
	GameObject(sf::FloatRect(pos.x, pos.y, 20, 20)),
	MAX_SPEED(rand() % 1000 + 1000),
	MAX_ACCEL(rand() % 500 + 500),
	m_shape(sf::RectangleShape(sf::Vector2f(20, 20))),
	MAX_TIME_UNTIL_SHOOT(0.2f),
	m_timeUntilShoot(0)
{
	m_shape.setFillColor(sf::Color::Cyan);
	m_shape.setPosition(m_position.toSFMLVector());
}

Vector2D Mutant::getPosition()
{
	return m_position;
}

Vector2D Mutant::getVelocity()
{
	return m_velocity;
}

bool Mutant::isPredator()
{
	return false;
}

void Mutant::Update(float dt)
{
	m_timeUntilShoot -= dt;
	Vector2D dir(0, 0);
	Vector2D playerPos = AIManager::getClosestPlayerPos(m_position);
	if (Vector2D::Distance(playerPos, m_position) < 400)
	{
		if (m_timeUntilShoot < 0)
		{
			EntityFactory::CreateBullet(m_position, (playerPos - m_position).Normalize());
			m_timeUntilShoot = MAX_TIME_UNTIL_SHOOT;
		}
	}
	AIManager::seekToward(m_position, playerPos, dir);
	m_acceleration = dir * MAX_ACCEL;

	AIManager::swarm(this, m_position, m_acceleration);
	PhysicsManager::accelerateVelocity(dt, m_velocity, m_acceleration, MAX_ACCEL);
	PhysicsManager::move(dt, m_position, m_velocity);
	
	m_shape.setPosition(m_position.toSFMLVector());
	m_bounds.left = m_position.x;
}

void Mutant::Draw(sf::RenderWindow& w)
{
	w.draw(m_shape);
}

void Mutant::DrawWithXOffset(sf::RenderWindow & window, float xOffset)
{
	m_shape.move(sf::Vector2f(xOffset, 0));
	window.draw(m_shape);
	m_shape.move(sf::Vector2f(-xOffset, 0));
}

void Mutant::wrapPositions(Camera & cam)
{
	cam.Wrap(m_position);
	m_shape.setPosition(m_position.toSFMLVector());
}
