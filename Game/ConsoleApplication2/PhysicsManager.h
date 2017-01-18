#pragma once
#include "Vector2D.h"
#include <iostream>

class PhysicsManager
{
public:
	static void move(float dt, Vector2D& position, Vector2D& velocity);
	static void accelerate(float dt, Vector2D& speed, Vector2D acceleration, Vector2D targetSpeed);
	static void accelerateVelocity(float dt, Vector2D& velocity, Vector2D acceleration, const float speedLimit);
	static void BindPositionToLevel(Vector2D& m_position, Vector2D& m_direction);
	static void BindPositionToLevel(Vector2D& m_position);
	static void ApplyFriction(float dt, Vector2D & velocity, float mFriction=0.01f);
	static void VerticalWrapPosition(Vector2D& m_position);
	static void initialize(sf::FloatRect levelBounds);
	static Vector2D getRandomPosition();
	static sf::FloatRect getLevelBounds();

private:
	static sf::FloatRect m_levelBounds;
};
