#include "stdafx.h"
#include "PowerUp.h"


PowerUp::PowerUp(int type, sf::Vector2f position, sf::Vector2f size) 
	: GameObject(sf::FloatRect(position, size)),
	  m_type(type),
	  m_timeToLive(5),
	  m_position(position)
{
	initializeColor();
	m_shape = sf::RectangleShape(size);
	m_shape.setPosition(position);
	m_shape.setFillColor(m_color);
}


PowerUp::~PowerUp()
{
}


void PowerUp::initializeColor()
{
	switch (m_type)
	{
	case PowerUpTypes::HYPERJUMP:
		m_color = sf::Color(66, 134, 244, 255);
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

int PowerUp::GetType()
{
	return m_type;
}
