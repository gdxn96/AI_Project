#include "stdafx.h"
#include "Terrain.h"

Terrain::Terrain(int maxPoints, int mapWidth)
{
	int previousY = 0;
	float xMultiplier = 9 * (static_cast<float>(mapWidth) / maxPoints);
	int dev = 20;
	for (int i = 0; i < maxPoints; i++)
	{
		m_points.push_back(sf::Vertex(sf::Vector2f(i * xMultiplier, 1000 + previousY + rand() % dev - dev)));
		previousY = m_points[i].texCoords.y;
	}
}

void Terrain::Update(float dt)
{
}

void Terrain::Draw(sf::RenderWindow & r)
{
	const sf::Vertex* x = &m_points[0];
	r.draw(x, m_points.size(), sf::LinesStrip);
}
