#pragma once

#include "GameObject.h"
#include "AIManager.h"
#include "Astronaut.h"

class Astronaut;

class Abductor : public GameObject, public Boid
{
private:
	Vector2D m_direction;
	Vector2D m_velocity;
	sf::FloatRect m_patrolArea;
	Vector2D m_position;
	float m_seekDistance;
	sf::RectangleShape m_shape;
	Vector2D m_speed;
	const int MAX_WANDER_TIME;
	float m_wanderTimeRemaining;
	Astronaut* m_targetAstronaut;

	bool isInPatrolArea();

public:
	Abductor(sf::Vector2f position, sf::Vector2f size, float minPatrolHeight, float maxPatrolHeight);
	~Abductor();
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void DrawWithXOffset(sf::RenderWindow& window, float xOffset) override;
	void wrapPositions(Camera& cam);
	void setTargetAstronaut(Astronaut* a);

	Vector2D getPosition() override;
	Vector2D getVelocity() override;
	bool isPredator() override;
};
