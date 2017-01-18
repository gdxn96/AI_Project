#pragma once

#include "HealthObject.h"
#include "AIManager.h"
#include "Astronaut.h"

class Astronaut;


class Abductor : public HealthObject, public Boid
{
private:
	sf::RectangleShape m_shape;
	Vector2D m_size;

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
	enum m_states { TOSURFACE, PATROL, PATROL_EXIT, SEEK, ABDUCT, TRANSFORM };

	// Actions
	float m_abductDistance;
	Vector2D m_abductPosition;
	Astronaut* m_closestAstronaut;
	Vector2D m_closestAstronautPosition;
	float m_seekDistance;
	const int FIRE_RANGE;
	const float FIRE_RATE;
	float m_timeTillFire;

	bool isInPatrolArea();
	bool shouldAbductAstronaut();
	bool shouldSeekAstronaut();


public:
	Abductor(sf::Vector2f position, sf::Vector2f size, float minPatrolHeight, float maxPatrolHeight);
	virtual ~Abductor();
	void Update(float dt) override;
	void UpdateShooting(float dt);
	void UpdateState();
	void Draw(sf::RenderWindow& window) override;
	void DrawWithXOffset(sf::RenderWindow& window, float xOffset) override;
	void wrapPositions(Camera& cam);
	void setClosestAstronaut(Vector2D position, Astronaut* a);
	void dropAstronaut();
	void calculateAbductPosition();

	Vector2D getPosition() override;
	Vector2D getVelocity() override;
	bool isAbducting();
	bool isPatrolling();
	bool isPredator() override;
	bool shouldTransform();
};
