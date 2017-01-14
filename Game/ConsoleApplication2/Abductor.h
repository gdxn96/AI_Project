#pragma once

#include "GameObject.h"
#include "AIManager.h"


class Abductor : public GameObject
{
private:
	Vector2D m_direction;
	sf::FloatRect m_patrolArea;
	Vector2D m_position;
	float m_seekDistance;
	sf::RectangleShape m_shape;
	Vector2D m_speed;
	const int MAX_WANDER_TIME;
	float m_wanderTimeRemaining;

	bool isInPatrolArea();

public:
	Abductor(sf::Vector2f position, sf::Vector2f size, float minPatrolHeight, float maxPatrolHeight);
	~Abductor();
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void DrawWithXOffset(sf::RenderWindow& window, float xOffset) override;
	void wrapPositions(Camera& cam);
};