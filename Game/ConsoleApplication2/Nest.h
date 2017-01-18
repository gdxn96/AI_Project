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

	void SpawnAbductors(float dt);
	void destroyElectrics();
	void setGroundY(float y);
	bool isUnderEMP();

private:
	enum States {WANDERING, EVADING };
	Vector2D m_position;
	Vector2D m_velocity, m_direction;
	const float MAX_SPEED;
	float m_timeUntilChangeDirection;
	float m_timeUntilShoot;
	const float MAX_TIME_UNTIL_SHOOT;

	float m_timeUntilAbductorSpawn;
	const float MAX_TIME_UNTIL_ABDUCTOR_SPAWN;
	const int MAX_TIME;
	sf::RectangleShape m_shape;
	States m_state;
	const float MAX_ACCEL;
	Vector2D m_acceleration;
	float m_groundY;
	const int MAX_EMP_TIME;
	float m_timetillEMPEnds;
};
