#pragma once
#include "Vector2D.h"
#include <iostream>

class PhysicsManager
{
public:
	static void move(float dt, Vector2D& position, Vector2D& velocity);
	static void accelerate(float dt, Vector2D& speed, Vector2D acceleration, Vector2D targetSpeed);
	static void BindPositionToLevel(Vector2D& m_position, Vector2D& m_direction);
	static void BindPositionToLevel(Vector2D& m_position);

	static void initialize(sf::FloatRect levelBounds);
private:
	static sf::FloatRect m_levelBounds;
};
