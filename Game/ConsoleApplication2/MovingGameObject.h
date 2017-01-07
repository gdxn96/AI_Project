#pragma once

#include "GameObject.h"
#include "Constants.h"


class MovingGameObject : public GameObject
{
public:
	// With acceleration
	MovingGameObject(Rect bounds, Vector2D acceleration, Vector2D maxSpeed, bool isMiniMapObject = false)
		: GameObject(bounds),
		m_ACCELERATION(acceleration),
		m_MAXSPEED(maxSpeed) {}

	// Without acceleration
	MovingGameObject(Rect bounds, Vector2D maxSpeed, bool isMiniMapObject = false)
		: GameObject(bounds),
		m_ACCELERATION(sf::Vector2f(-1, -1)),
		m_MAXSPEED(maxSpeed),
		m_speed(maxSpeed) {}

protected:
	const Vector2D m_ACCELERATION;
	const Vector2D m_MAXSPEED;

	Vector2D m_direction;
	Vector2D m_speed;


	virtual void UpdatePosition(float dt)
	{
		m_bounds.pos.x += (m_direction.x * (m_speed.x * dt));
		m_bounds.pos.y += (m_direction.y * (m_speed.y * dt));
	}

	virtual void UpdateXSpeed(float dt, int multiplier, float targetSpeed)
	{
		float speedChange = (m_ACCELERATION.x * dt) * multiplier;
		m_speed.x += speedChange;
		m_speed.x = abs(m_speed.x - targetSpeed) <= abs(speedChange) * 2 ? targetSpeed : m_speed.x;
	}

	virtual void UpdateYSpeed(float dt, int multiplier, float targetSpeed)
	{
		float speedChange = (m_ACCELERATION.y * dt) * multiplier;
		m_speed.y += speedChange;
		m_speed.y = abs(m_speed.y - targetSpeed) <= abs(speedChange) * 2 ? targetSpeed : m_speed.y;
	}
};