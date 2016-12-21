#include "stdafx.h"
#include "TerrainSegment.h"

TerrainSegment::TerrainSegment(sf::ConvexShape shape) : GameObject(true), m_shape(shape)
{
	//m_shape.
}

void TerrainSegment::Update(float dt)
{
}

void TerrainSegment::Draw(sf::RenderWindow & window)
{
	window.draw(m_shape);
}
