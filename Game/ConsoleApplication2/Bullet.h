#pragma once

#include "MovingGameObject.h"


class Bullet : public MovingGameObject
{
private:
	float m_timeToLive;

public:
	Bullet(Vector2D pos, Vector2D dir);
	~Bullet();
	void Update(float dt) override;
	void Draw(sf::RenderWindow& w) override;
	bool isAlive();
};