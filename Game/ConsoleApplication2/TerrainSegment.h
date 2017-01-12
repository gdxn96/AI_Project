#pragma once
#include "GameObject.h"

class TerrainSegment : public GameObject
{
public:
	TerrainSegment(sf::ConvexShape shape);
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void DrawWithXOffset(sf::RenderWindow& window, float xOffset) override;

private:
	sf::ConvexShape m_shape;
};