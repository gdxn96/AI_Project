#pragma once

#include "MovingGameObject.h"


class Bullet : public MovingGameObject
{
private:
	float m_timeToLive;

public:
	Bullet();
	Bullet(sf::Vector2f pos, sf::Vector2f dir);
	~Bullet();
	void Update(float dt) override;
	void Draw(sf::RenderWindow& w) override;
	bool isAlive();
};