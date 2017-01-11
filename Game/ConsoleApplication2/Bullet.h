#pragma once

#include "GameObject.h"


class Bullet : public GameObject
{
private:
	Vector2D m_velocity;
	float m_timeToLive;

public:
	Bullet(Vector2D pos, Vector2D dir);
	~Bullet();
	void Update(float dt) override;
	void Draw(sf::RenderWindow& w) override;
	bool isAlive();
};