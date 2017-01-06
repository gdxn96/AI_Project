#pragma once

#include "GameObject.h"
#include "AIManager.h"


class Astronaut : public GameObject
{
private:
	Vector2D m_direction;
	float m_speed;
	const int m_directionChangeTimeMax; // as seconds
	float m_directionChangeTimeRemaining;
	sf::RectangleShape m_sprite;

	void move(float dt);

public:
	Astronaut(Rect rectangle, bool isMiniMapObject);
	void Update(float dt) override;
	void Draw(sf::RenderWindow& w) override;
};