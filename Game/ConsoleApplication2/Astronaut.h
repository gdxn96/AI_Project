#pragma once

#include "AIGameObject.h"
#include "AIManager.h"


class Astronaut : public AIGameObject
{
private:
	const int m_maxWanderTime; // in seconds
	float m_wanderTimeRemaining;
	sf::RectangleShape m_shape;
	Vector2D m_position;

public:
	Astronaut(Vector2D position, bool isMiniMapObject);
	void Update(float dt) override;
	void Draw(sf::RenderWindow& w) override;
	void DrawWithXOffset(sf::RenderWindow& window, float xOffset) override;
	void wrapPositions(Camera& cam) override;
};