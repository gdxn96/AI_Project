#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "AIManager.h"
#include "EntityFactory.h"

class Meteor : public GameObject
{
public:
	Meteor(Vector2D position, float radius, float speed);
	~Meteor();
	void Update(float dt) override;
	void Draw(sf::RenderWindow& w) override;
	void DrawWithXOffset(sf::RenderWindow& window, float xOffset) override;
	void wrapPositions(Camera& cam) override;
	Vector2D getPosition();
private:
	float m_speed;
	Vector2D m_position;
	sf::CircleShape m_shape;
	Vector2D m_direction;
};