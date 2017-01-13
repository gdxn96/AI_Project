#include "stdafx.h"
#include "Abductor.h"



Abductor::Abductor(sf::Vector2f position, sf::Vector2f size, float minPatrolHeight, float maxPatrolHeight) 
	: GameObject(sf::FloatRect(position, size), true),
	  m_maxPatrolHeight(maxPatrolHeight),
	  m_minPatrolHeight(minPatrolHeight),
	  m_position(position),
	  m_shape(size),
	  m_speed(300, 300)
{
	m_shape.setPosition(m_position.toSFMLVector());
}

Abductor::~Abductor() { }



void Abductor::Update(float dt)
{
	if (isInPatrolArea())
	{
		//Boid::seekToward();
	}

	PhysicsManager::move(dt, m_position, m_direction * m_speed);
}

void Abductor::Draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
}

void Abductor::DrawWithXOffset(sf::RenderWindow& window, float xOffset)
{
	m_shape.move(sf::Vector2f(xOffset, 0));
	window.draw(m_shape);
	m_shape.move(sf::Vector2f(-xOffset, 0));
}



bool Abductor::isInPatrolArea()
{
	return m_position.y >= m_minPatrolHeight && m_position.y <= m_maxPatrolHeight;
}