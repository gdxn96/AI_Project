#pragma once
#include "GameObject.h"

class Terrain : public GameObject
{
public:
	Terrain(int maxPoints, int mapWidth);
	void Update(float dt) override;
	void Draw(sf::RenderWindow& r) override;

private:
	std::vector<sf::Vertex> m_points;
};
