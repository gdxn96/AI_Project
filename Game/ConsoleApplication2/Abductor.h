#pragma once

#include "GameObject.h"
#include "AIManager.h"
#include "Astronaut.h"

class Astronaut;


class Abductor : public GameObject, public Boid
{
private:
	sf::RectangleShape m_shape;

	// Movement
	Vector2D m_direction;
	Vector2D m_velocity;
	Vector2D m_position;
	Vector2D m_speed;

	// Wander/Patrol
	sf::FloatRect m_patrolArea;
	const int MAX_WANDER_TIME;
	float m_wanderTimeRemaining;

	// States
	int m_currentState;
	enum m_states { TOSURFACE, PATROL, PATROL_EXIT, SEEK, ABDUCT };

	// Actions
	float m_abductDistance;
	Astronaut* m_closestAstronaut;
	Vector2D m_closestAstronautPosition;
	float m_seekDistance;

	bool isInPatrolArea();
	bool shouldAbductAstronaut();
	bool shouldSeekAstronaut();


public:
	Abductor(sf::Vector2f position, sf::Vector2f size, float minPatrolHeight, float maxPatrolHeight);
	~Abductor();
	void Update(float dt) override;
	void UpdateState();
	void Draw(sf::RenderWindow& window) override;
	void DrawWithXOffset(sf::RenderWindow& window, float xOffset) override;
	void wrapPositions(Camera& cam);
	void setClosestAstronaut(Vector2D position, Astronaut* a);

	Vector2D getPosition() override;
	Vector2D getVelocity() override;
	bool isPredator() override;
};
