#include "stdafx.h"
#include "Meteor.h"

Meteor::Meteor(Vector2D position, float radius, float speed) 
	: GameObject(sf::FloatRect(), true), 
	  m_position(position), 
	  m_speed(speed), 
	  m_shape(radius),
	  m_direction(RandomFloat(0, 3.14f))
{
	m_bounds.width = radius * 2;
	m_bounds.height = radius * 2;
	m_bounds.left = m_position.x;
	m_bounds.top = m_position.y;

	m_shape.setPosition(position.toSFMLVector());
	m_shape.setTexture(AssetLoader::getInstance()->findTextureByKey("meteor"));
}

Meteor::~Meteor()
{
	AIManager::unregisterMeteor(this);
}

void Meteor::Update(float dt)
{
	PhysicsManager::move(dt, m_position, m_direction * m_speed);
	PhysicsManager::VerticalWrapPosition(m_position);
	
	m_shape.setPosition(m_position.toSFMLVector());
	m_bounds.left = m_position.x;
	m_bounds.top = m_position.y;
}

void Meteor::Draw(sf::RenderWindow & w)
{
	w.draw(m_shape);

	sf::RectangleShape r(sf::Vector2f(m_shape.getGlobalBounds().width, m_shape.getGlobalBounds().height));
	r.setPosition(sf::Vector2f(m_shape.getGlobalBounds().left, m_shape.getGlobalBounds().top));
	r.setFillColor(sf::Color::Transparent);
	r.setOutlineThickness(1);
	r.setOutlineColor(sf::Color::Red);
	w.draw(r);
}

void Meteor::DrawWithXOffset(sf::RenderWindow & window, float xOffset)
{
	m_shape.move(sf::Vector2f(xOffset, 0));
	window.draw(m_shape);
	m_shape.move(sf::Vector2f(-xOffset, 0));
}

void Meteor::wrapPositions(Camera & cam)
{
	cam.Wrap(m_position);
	m_shape.setPosition(m_position.toSFMLVector());
}

Vector2D Meteor::getPosition()
{
	return m_position + Vector2D(m_bounds.width / 2, m_bounds.width / 2);
}
