#pragma once

#include "GameObject.h"
#include "AIManager.h"


class Abductor : GameObject
{
private:
	Vector2D m_direction;
	float m_minPatrolHeight;
	float m_maxPatrolHeight;
	Vector2D m_position;
	sf::RectangleShape m_shape;
	Vector2D m_speed;

	bool isInPatrolArea();

public:
	Abductor(sf::Vector2f position, sf::Vector2f size, float minPatrolHeight, float maxPatrolHeight);
	~Abductor();
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void DrawWithXOffset(sf::RenderWindow& window, float xOffset) override;
};