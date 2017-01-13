#include "stdafx.h"
#include "PhysicsManager.h"

sf::FloatRect PhysicsManager::m_levelBounds = sf::FloatRect();

void PhysicsManager::move(float dt, Vector2D& position, Vector2D& velocity)
{
	position += (velocity * dt);
}

void PhysicsManager::accelerate(float dt, Vector2D& speed, Vector2D acceleration, Vector2D targetSpeed)
{
	Vector2D speedChange = acceleration * dt;
	speed += speedChange;
	speed.x = abs(speed.x - targetSpeed.x) <= abs(speedChange.x) * 2 ? targetSpeed.x : speed.x;
	speed.y = abs(speed.y - targetSpeed.y) <= abs(speedChange.y) * 2 ? targetSpeed.y : speed.y;
}

void PhysicsManager::BindPositionToLevel(Vector2D& m_position, Vector2D& m_direction)
{
	if (m_position.y < m_levelBounds.top)
	{
		m_direction.y *= -1;
		m_position.y = m_levelBounds.top;
	}
	else if (m_position.y > m_levelBounds.height + m_levelBounds.top)
	{
		m_direction.y *= -1;
		m_position.y = m_levelBounds.height + m_levelBounds.top;
	}
}

void PhysicsManager::BindPositionToLevel(Vector2D& m_position)
{
	if (m_position.y < m_levelBounds.top)
	{
		m_position.y = m_levelBounds.top;
	}
	else if (m_position.y > m_levelBounds.height + m_levelBounds.top)
	{
		m_position.y = m_levelBounds.height + m_levelBounds.top;
	}
}

void PhysicsManager::VerticalWrapPosition(Vector2D & m_position)
{
	if (m_position.y > m_levelBounds.height * 1.5f)
	{
		m_position.y = -m_levelBounds.height * .5f;
	}
}

void PhysicsManager::initialize(sf::FloatRect levelBounds)
{
	m_levelBounds = levelBounds;
}
