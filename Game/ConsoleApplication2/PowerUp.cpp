#include "stdafx.h"
#include "PowerUp.h"


PowerUp::PowerUp(int type, sf::Vector2f position, sf::Vector2f size) 
	: GameObject(sf::FloatRect(position, size)),
	  m_type(type),
	  m_timeToLive(10),
	  m_position(position)
{
	initializeColor();
	m_shape = sf::RectangleShape(size);
	m_shape.setPosition(position);
	m_shape.setFillColor(m_color);
	m_bounds.left = m_position.x;
	m_bounds.top = m_position.y;
}


PowerUp::~PowerUp()
{
}


void PowerUp::initializeColor()
{
	switch (m_type)
	{
	case PowerUpTypes::HYPERJUMP:
		m_color = sf::Color(255, 140, 241, 255); // pink
		break;
	case PowerUpTypes::MORE_FIRE_RATE:
		m_color = sf::Color(140, 255, 142, 255); // light green
		break;
	case PowerUpTypes::INVINCIBILITY:
		m_color = sf::Color(252, 30, 30, 255); // Red
		break;
	case PowerUpTypes::EMP:
		m_color = sf::Color(30, 215, 252, 255); // light blue
		break;
	}
}


void PowerUp::Update(float dt)
{
	m_timeToLive -= dt;

	if (m_timeToLive <= 0)
	{
		kill();
	}
}

void PowerUp::Draw(sf::RenderWindow & window)
{
	window.draw(m_shape);
}

void PowerUp::DrawWithXOffset(sf::RenderWindow & window, float xOffset)
{
	m_shape.move(sf::Vector2f(xOffset, 0));
	window.draw(m_shape);
	m_shape.move(sf::Vector2f(-xOffset, 0));
}

void PowerUp::wrapPositions(Camera & cam)
{
	cam.Wrap(m_position);
	m_shape.setPosition(m_position.toSFMLVector());
}

int PowerUp::GetType()
{
	return m_type;
}
