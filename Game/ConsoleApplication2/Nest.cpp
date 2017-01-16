#include "stdafx.h"
#include "Nest.h"
#include "EntityFactory.h"

Nest::Nest(Vector2D pos, Vector2D dir, float speed)
	: GameObject(sf::FloatRect(pos.x, pos.y, 40, 40), true),
	m_shape(sf::Vector2f(40, 40)),
	m_position(pos),
	m_direction((0,0)),
	m_velocity(dir * speed),
	MAX_TIME(10),
	m_timeUntilChangeDirection(0),
	m_state(WANDERING),
	MAX_TIME_UNTIL_SHOOT(5),
	m_timeUntilShoot(0),
	MAX_ACCEL(20),
	MAX_SPEED(speed)
{
	m_shape.setPosition(pos.toSFMLVector());
	m_shape.setFillColor(sf::Color::Yellow);
}

void Nest::Draw(sf::RenderWindow & window)
{
	window.draw(m_shape);
}

void Nest::Update(float dt)
{
	m_timeUntilShoot -= dt;
	m_acceleration = 0;

	switch (m_state)
	{
	case WANDERING:
		
		AIManager::wander(dt, m_timeUntilChangeDirection, MAX_TIME, m_direction, false);
		m_velocity = m_direction * MAX_SPEED;
		PhysicsManager::move(dt, m_position, m_velocity);

		if (Vector2D::Distance(AIManager::getClosestPlayerPos(m_position), m_position) < 500)
		{
			m_state = EVADING;
		}
		break;
	case EVADING:
		if (m_timeUntilShoot < 0)
		{
			EntityFactory::CreateMissile(m_position);
			m_timeUntilShoot = MAX_TIME_UNTIL_SHOOT;
		}

		AIManager::avoid(m_position, AIManager::getClosestPlayerPos(m_position), m_acceleration, MAX_ACCEL);
		PhysicsManager::accelerateVelocity(dt, m_velocity, m_acceleration, MAX_SPEED);
		PhysicsManager::move(dt, m_position, m_velocity);

		if (Vector2D::Distance(AIManager::getClosestPlayerPos(m_position), m_position) > 1200)
		{
			m_state = WANDERING;
			m_timeUntilChangeDirection = 0;
		}
		
		break;
	default:
		break;
	}

	PhysicsManager::BindPositionToLevel(m_position, m_velocity);

	m_shape.setPosition(m_position.toSFMLVector());
	m_bounds.left = m_position.x;
	m_bounds.top = m_position.y;
	
}

void Nest::DrawWithXOffset(sf::RenderWindow & window, float xOffset)
{
	m_shape.move(sf::Vector2f(xOffset, 0));
	window.draw(m_shape);
	m_shape.move(sf::Vector2f(-xOffset, 0));
}

void Nest::wrapPositions(Camera & cam)
{
	cam.Wrap(m_position);
	m_shape.setPosition(m_position.toSFMLVector());
}
