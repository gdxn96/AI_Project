#pragma once
#include "HealthObject.h"
#include "Boid.h"

class Mutant : public HealthObject, public Boid
{
public:
	Mutant(Vector2D pos);
	Vector2D getPosition();
	Vector2D getVelocity();
	bool isPredator();

	void Update(float dt);
	void Draw(sf::RenderWindow& window);
	void DrawWithXOffset(sf::RenderWindow& window, float xOffset);
	void wrapPositions(Camera & cam);
private:
	Vector2D m_position, m_acceleration, m_velocity;
	const float MAX_SPEED, MAX_ACCEL;
	sf::RectangleShape m_shape;
	float m_timeUntilShoot;
	const float MAX_TIME_UNTIL_SHOOT;
};
