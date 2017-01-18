#include "stdafx.h"
#include "Nest.h"
#include "EntityFactory.h"

Nest::Nest(Vector2D pos, Vector2D dir, float speed)
	: HealthObject(50, sf::FloatRect(pos.x, pos.y, 121, 80), true),
	m_shape(sf::Vector2f(121, 80)),
	m_position(pos),
	m_direction((0,0)),
	m_velocity(dir * speed),
	MAX_TIME(5),
	m_timeUntilChangeDirection(0),
	m_state(WANDERING),
	MAX_TIME_UNTIL_SHOOT(5),
	m_timeUntilShoot(0),
	MAX_ACCEL(50000),
	MAX_SPEED(speed),
	MAX_TIME_UNTIL_ABDUCTOR_SPAWN(10),
	m_timeUntilAbductorSpawn(0),
	MAX_EMP_TIME(5),
	m_timetillEMPEnds(0)
{
	m_shape.setPosition(pos.toSFMLVector());
	//m_shape.setFillColor(sf::Color::Yellow);
	m_shape.setTexture(AssetLoader::getInstance()->findTextureByKey("nest"));
}

void Nest::Draw(sf::RenderWindow & window)
{
	window.draw(m_shape);
}

void Nest::Update(float dt)
{
	if (isUnderEMP())
	{
		m_timetillEMPEnds -= dt;
		PhysicsManager::move(dt, m_position, m_velocity);

		if (m_position.y >= m_groundY)
		{
			m_position.y = m_groundY;
		}
	}
	else
	{
		m_timeUntilShoot -= dt;

		switch (m_state)
		{
		case WANDERING:

			AIManager::wanderThrust(dt, m_timeUntilChangeDirection, MAX_TIME, m_velocity, m_acceleration, MAX_ACCEL);

			if (Vector2D::Distance(AIManager::getClosestPlayerPos(m_position), m_position) < 800)
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
			if (Vector2D::Distance(AIManager::getClosestPlayerPos(m_position), m_position) > 1400)
			{
				m_state = WANDERING;
				m_timeUntilChangeDirection = 0;
			}

			break;
		default:
			break;
		}
		AIManager::avoidObstacles(m_position, m_acceleration, MAX_ACCEL);
		PhysicsManager::accelerateVelocity(dt, m_velocity, m_acceleration, MAX_SPEED);
		PhysicsManager::move(dt, m_position, m_velocity);
		PhysicsManager::BindPositionToLevel(m_position, m_velocity);
		PhysicsManager::BindPositionToLevel(m_position, m_acceleration);
		PhysicsManager::ApplyFriction(dt, m_velocity, 0.1f);

		SpawnAbductors(dt);
	}
	

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

void Nest::SpawnAbductors(float dt)
{
	m_timeUntilAbductorSpawn -= dt;
	if (m_timeUntilAbductorSpawn < 0)
	{
		EntityFactory::CreateAbductor(m_position.toSFMLVector());
		m_timeUntilAbductorSpawn = MAX_TIME_UNTIL_ABDUCTOR_SPAWN;
	}
}

void Nest::destroyElectrics()
{
	m_velocity = Vector2D::DOWN;
	m_velocity = m_velocity * MAX_SPEED;
	m_timetillEMPEnds = MAX_EMP_TIME;
}

void Nest::setGroundY(float y)
{
	m_groundY = y;
}

bool Nest::isUnderEMP()
{
	return m_timetillEMPEnds > 0;
}