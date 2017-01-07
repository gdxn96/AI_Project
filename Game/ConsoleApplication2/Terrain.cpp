#include "stdafx.h"
#include "Terrain.h"

bool Terrain::valid(int value, int max, int min)
{
	return value > min && value < max;
}

std::vector<int> Terrain::calculateYValues(float minY, float maxY, float displace, float roughness) 
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


std::vector<TerrainSegment*> Terrain::GenerateTerrain(int minY, int maxY, Vector2D levelSize)
{
	sf::ConvexShape shape;
	shape.setPointCount(4);
	std::vector<int> yPoints = calculateYValues(minY, maxY, levelSize.h, 0.6f);
	float xOffset = static_cast<float>(levelSize.w) / yPoints.size();
	sf::Vertex prev;
	sf::Vertex currentVertex;
	std::vector<TerrainSegment*> terrainSegments;
	std::vector<sf::Vertex> vertices;

	for (int i = 0; i < yPoints.size(); i++)
	{
		
		currentVertex = sf::Vertex(sf::Vector2f(i * xOffset, yPoints[i]));
		
		if (i != 0)
		{
			shape.setPointCount(4);
			shape.setPoint(0, prev.position);
			shape.setPoint(1, sf::Vector2f(prev.position.x, levelSize.h));
			shape.setPoint(2, sf::Vector2f(currentVertex.position.x, levelSize.h));
			shape.setPoint(3, currentVertex.position);
			
			shape.setFillColor(sf::Color(112, 89, 40));

			terrainSegments.push_back(new TerrainSegment(shape));
		}

		prev = currentVertex;
		vertices.push_back(currentVertex);
	}

	//join up first with last point
	shape.setPointCount(4);
	shape.setPoint(0, vertices.back().position - sf::Vector2f(levelSize.x, 0));
	shape.setPoint(1, sf::Vector2f(vertices.back().position.x - levelSize.x, levelSize.h));
	shape.setPoint(2, sf::Vector2f(vertices.front().position.x, levelSize.h));
	shape.setPoint(3, vertices.front().position);

	shape.setFillColor(sf::Color(112, 89, 40));

	terrainSegments.push_back(new TerrainSegment(shape));

	return terrainSegments;
}

