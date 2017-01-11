#pragma once

#include "GameObject.h"
#include "Constants.h"
#include "AIManager.h"


class AIGameObject : public GameObject
{
public:
	// With acceleration
	AIGameObject(Rect bounds, Vector2D acceleration, Vector2D maxSpeed, bool isMiniMapObject = false)
		: GameObject(bounds, isMiniMapObject),
		ACCELERATION(acceleration),
		MAX_SPEED(maxSpeed) {}

	// Without acceleration
	AIGameObject(Rect bounds, Vector2D maxSpeed, bool isMiniMapObject = false)
		: GameObject(bounds, isMiniMapObject),
		ACCELERATION(Vector2D(0, 0)),
		MAX_SPEED(maxSpeed),
		m_speed(maxSpeed) {}

protected:
	const Vector2D ACCELERATION;
	const Vector2D MAX_SPEED;
	Vector2D m_direction;
	Vector2D m_speed;
};