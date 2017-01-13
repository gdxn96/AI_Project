#pragma once
#include "SimpleTypes.h"
#include "GameObject.h"
#include "AIManager.h"

class Nest : public GameObject
{
public:
	Nest(Vector2D pos, Vector2D dir, float speed);
	void Draw(sf::RenderWindow& window) override;
	void Update(float dt) override;
	void DrawWithXOffset(sf::RenderWindow& window, float xOffset) override;
	void wrapPositions(Camera& cam) override;

private:
	Vector2D m_position;
	Vector2D m_direction;
	float m_speed;
	float m_timeUntilChangeDirection;
	const int MAX_TIME;
	sf::RectangleShape m_shape;
};
