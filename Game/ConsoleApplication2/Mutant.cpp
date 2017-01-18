#include "stdafx.h"
#include "Mutant.h"
#include "PhysicsManager.h"
#include "AIManager.h"
#include "EntityFactory.h"

Mutant::Mutant(Vector2D pos) :
	Boid(false),
	HealthObject(100, sf::FloatRect(pos.x, pos.y, 60, 60)),
	MAX_SPEED(rand() % 1000 + 1000),
	MAX_ACCEL(rand() % 1000 + 1000),
	m_shape(sf::RectangleShape(sf::Vector2f(60, 60))),
	MAX_TIME_UNTIL_SHOOT(0.2f),
	m_timeUntilShoot(0),
	MAX_EMP_TIME(5),
	m_position(pos),
	m_timetillEMPEnds(0)
{
	m_shape.setTexture(AssetLoader::getInstance()->findTextureByKey("abductor"));
	m_shape.setFillColor(sf::Color::Red);
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
		Vector2D dir(0, 0);
		Vector2D playerPos = AIManager::getClosestPlayerPos(m_position);
		if (Vector2D::Distance(playerPos, m_position) < 400)
		{
			if (m_timeUntilShoot < 0)
			{
				EntityFactory::CreateBullet(m_position, (playerPos - m_position).Normalize(), true);
				m_timeUntilShoot = MAX_TIME_UNTIL_SHOOT;
			}
		}
		AIManager::seekToward(m_position, playerPos, dir);
		m_acceleration = dir * MAX_ACCEL;

		AIManager::avoidObstacles(m_position, m_acceleration, MAX_ACCEL);
		AIManager::swarm(this, m_position, m_acceleration);
		PhysicsManager::accelerateVelocity(dt, m_velocity, m_acceleration, MAX_ACCEL);
		PhysicsManager::move(dt, m_position, m_velocity);
	}
	
	m_shape.setPosition(m_position.toSFMLVector());
	m_bounds.left = m_position.x;
	m_bounds.top = m_position.y;
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

void Mutant::destroyElectrics()
{
	m_velocity = Vector2D::DOWN;
	m_velocity = m_velocity * MAX_SPEED;
	m_timetillEMPEnds = MAX_EMP_TIME;
}

void Mutant::setGroundY(float y)
{
	m_groundY = y;
}

bool Mutant::isUnderEMP()
{
	return m_timetillEMPEnds > 0;
}