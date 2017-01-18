#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(Vector2D pos, Vector2D dir)
:	GameObject(sf::FloatRect(pos.x, pos.y, 20, 20)),
	Damageable(20),
	m_velocity(Vector2D(1200, 1200) * dir),
	m_position(pos),
	m_timeToLive(1),
	m_shape(sf::Vector2f(20,10))
{
	float angle = Vector2D::AngleDeg(m_velocity, Vector2D(0));
	m_shape.setRotation(angle);
	m_shape.setPosition(m_position.toSFMLVector());
	m_bounds.left = m_position.x;
	m_bounds.top = m_position.y;
	m_shape.setTexture(AssetLoader::getInstance()->findTextureByKey("bullet"));
}

Bullet::~Bullet() { 
}


void Bullet::Update(float dt)
{
	PhysicsManager::move(dt, m_position, m_velocity);
	
	if (m_timeToLive > 0)
	{
		m_timeToLive -= dt;
	}
	else
	{
		kill();
	}

	m_shape.setPosition(m_position.toSFMLVector());
	m_bounds.left = m_position.x;
	m_bounds.top = m_position.y;
}

void Bullet::wrapPositions(Camera & cam)
{
	cam.Wrap(m_position);
	m_shape.setPosition(m_position.toSFMLVector());
}

void Bullet::Draw(sf::RenderWindow& w)
{
	w.draw(m_shape);
}

void Bullet::DrawWithXOffset(sf::RenderWindow & window, float xOffset)
{
	m_shape.move(sf::Vector2f(xOffset, 0));
	window.draw(m_shape);
	m_shape.move(sf::Vector2f(-xOffset, 0));
}