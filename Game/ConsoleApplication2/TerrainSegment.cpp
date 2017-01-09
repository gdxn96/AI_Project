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
	window.draw(m_shape);
}

void TerrainSegment::DrawWithXOffset(sf::RenderWindow & window, float xOffset)
{
	m_shape.move(sf::Vector2f(xOffset, 0));
	window.draw(m_shape);
	m_shape.move(sf::Vector2f(-xOffset, 0));
}
