#pragma once

#include "GameObject.h"
#include "AIManager.h"


class Astronaut : public GameObject
{
private:
	sf::RectangleShape m_shape;
	Vector2D m_size;
	bool m_beingAbducted;
	float m_groundY;

	// Movement
	Vector2D m_direction;
	Vector2D m_position;
	Vector2D m_speed;

	// Wandering 
	const int MAX_WANDER_TIME; // in seconds
	float m_wanderTimeRemaining;

	void fall(float dt);

public:
	Astronaut(sf::Vector2f position, sf::Vector2f size);
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void DrawWithXOffset(sf::RenderWindow& window, float xOffset) override;
	void wrapPositions(Camera& cam) override;
	Vector2D getPosition();
	Vector2D getSize();
	void setBeingAbducted(bool value);
	void setPosition(Vector2D position);
	bool isOnGround();
};