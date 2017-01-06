#pragma once

#include "GameObject.h"
#include "Constants.h"


class MovingGameObject : public GameObject
{
public:
	MovingGameObject() { };
	MovingGameObject(sf::Vector2f position, sf::Vector2f size, sf::Vector2f acceleration, sf::Vector2f maxSpeed)
		: m_ACCELERATION(acceleration),
		  m_MAXSPEED(maxSpeed),
		  m_bounds(sf::RectangleShape(size)),
		  m_position(position)
	{
		m_bounds.setPosition(m_position);
	}

protected:
	const sf::Vector2f m_ACCELERATION;
	const sf::Vector2f m_MAXSPEED;

	sf::RectangleShape m_bounds;

	sf::Vector2f m_direction;
	sf::Vector2f m_position;
	sf::Vector2f m_speed;


	virtual void UpdatePosition(float dt)
	{
		m_position.x += (m_direction.x * (m_speed.x * dt));
		m_position.y += (m_direction.y * (m_speed.y * dt));
		m_bounds.setPosition(m_position);
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