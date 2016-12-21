#include "stdafx.h"
#include "TerrainSegment.h"

TerrainSegment::TerrainSegment(sf::ConvexShape shape) : GameObject(true, shape.getGlobalBounds()), m_shape(shape)
{
}

void TerrainSegment::Update(float dt)
{
}

void TerrainSegment::Draw(sf::RenderWindow & window)
{
	/*sf::RectangleShape r(sf::Vector2f(m_shape.getGlobalBounds().width, m_shape.getGlobalBounds().height));
	r.setPosition(sf::Vector2f(m_shape.getGlobalBounds().left, m_shape.getGlobalBounds().top));
	r.setFillColor(sf::Color::Transparent);
	r.setOutlineThickness(1);
	r.setOutlineColor(sf::Color::Red);
	window.draw(r);*/
	window.draw(m_shape);
}

void TerrainSegment::DrawWithXOffset(sf::RenderWindow & window, float xOffset)
{
	m_shape.move(sf::Vector2f(xOffset, 0));
	window.draw(m_shape);
	m_shape.move(sf::Vector2f(-xOffset, 0));
}
