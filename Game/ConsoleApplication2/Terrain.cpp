#include "stdafx.h"
#include "Terrain.h"

bool valid(int value, int max, int min)
{
	return value > min && value < max;
}

std::vector<int> calculateYValues(float minY, float maxY, float displace, float roughness) 
{
	int power = 2048; // has to be a power of two, since we're getting the midpoint of each line over and over again

	std::vector<int> points(power + 1);
	float initY = maxY - (maxY - minY / 2.f);

	// Set the initial left point
	do {
		points[0] = initY / 2 + (((double)rand() / (RAND_MAX)) * displace * 2) - displace;
	} while (!valid(points[0], maxY, minY));
	

	// set the initial right point
	points[power] = points[0];
	displace *= roughness;

	// Increase the number of segments
	for (int i = 1; i < power; i *= 2) 
	{
		// Iterate through each segment calculating the center point
		for (int j = (power / i) / 2; j < power; j += power / i) 
		{
			do
			{
				points[j] = ((points[j - (power / i) / 2] + points[j + (power / i) / 2]) / 2);
				points[j] += (((double)rand() / (RAND_MAX)) * displace * 2) - displace;
			} while (!valid(points[j], maxY, minY));
		}
		// reduce our random range
		displace *= roughness;
	}
	return points;
}


Terrain::Terrain(int minY, int maxY, Vector2D levelSize): GameObject(true)
{
	sf::ConvexShape s;
	s.setPointCount(4);
	std::vector<int> yPoints = calculateYValues(minY, maxY, levelSize.h, 0.6f);
	float xOffset = static_cast<float>(levelSize.w) / yPoints.size();
	sf::Vertex prev;
	sf::Vertex current;

	for (int i = 0; i < yPoints.size(); i++)
	{
		
		current = sf::Vertex(sf::Vector2f(i * xOffset, yPoints[i]));
		m_points.push_back(current);
		
		if (i != 0)
		{
			sf::ConvexShape s;
			s.setPointCount(4);
			s.setPoint(0, prev.position);
			s.setPoint(1, sf::Vector2f(prev.position.x, levelSize.h));
			s.setPoint(2, sf::Vector2f(current.position.x, levelSize.h));
			s.setPoint(3, current.position);
			
			s.setFillColor(sf::Color(112, 89, 40));

			m_terrainShapes.push_back(s);
		}

		prev = current;
	}
}


void Terrain::Update(float dt)
{
}

void Terrain::Draw(sf::RenderWindow & r)
{
	for (sf::ConvexShape terrainShape : m_terrainShapes)
	{
		r.draw(terrainShape);
	}
}
