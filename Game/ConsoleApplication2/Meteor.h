#pragma once
#include "GameObject.h"
#include "Vector2D.h"

class Meteor : public GameObject
{
public:
	Meteor(float radius, float speed, Vector2D direction, Vector2D position);
	void Update(float dt) override;
	void Draw(sf::RenderWindow& w) override;
	void DrawWithXOffset(sf::RenderWindow& window, float xOffset) override;
	void wrapPositions(Camera& cam) override;

private:
	float m_speed;
	Vector2D m_position;
	sf::CircleShape m_shape;
	Vector2D m_direction;
};