#pragma once
#include "GameObject.h"

class Missile : public GameObject
{
public:
	Missile(Vector2D pos);

	void Update(float dt) override;

	void wrapPositions(Camera & cam) override;

	void Draw(sf::RenderWindow & w) override;

	void DrawWithXOffset(sf::RenderWindow & window, float xOffset) override;
private:
	float m_timeToLive;
	const float MAX_SPEED;
	Vector2D m_position, m_velocity, m_acceleration;
	sf::RectangleShape m_shape;
};
