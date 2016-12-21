#pragma once
#include "GameObject.h"

class Terrain : public GameObject
{
public:
	Terrain(int minY, int maxY, Vector2D levelSize);
	void Update(float dt) override;
	void Draw(sf::RenderWindow& r) override;

private:
	std::vector<sf::Vertex> m_points;
	std::vector<sf::ConvexShape> m_terrainShapes;
};
