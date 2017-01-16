#include "stdafx.h"
#include "Mutant.h"
#include "PhysicsManager.h"
#include "AIManager.h"
#include "EntityFactory.h"

Mutant::Mutant(Vector2D pos) : 
	Boid(false), 
	GameObject(sf::FloatRect(pos.x, pos.y, 20, 20)), 
	MAX_SPEED(500), 
	m_state(SEEKING), 
	m_shape(sf::RectangleShape(sf::Vector2f(20, 20)))
{
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
	Vector2D direction;
	
	switch (m_state)
	{
	case Mutant::ATTACKING:
		EntityFactory::CreateBullet(m_position, direction);
		break;
	case Mutant::SEEKING:
		AIManager::seekToward(m_position, AIManager::getClosestPlayerPos(m_position), direction);
		m_velocity = direction * MAX_SPEED;
		break;
	default:
		break;
	}

	AIManager::swarm(this, m_position, m_acceleration);
	PhysicsManager::accelerateVelocity(dt, m_velocity, m_acceleration, MAX_SPEED);
	PhysicsManager::move(dt, m_position, m_velocity);

	cout << m_position.x << endl;

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
