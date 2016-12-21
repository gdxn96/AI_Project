#pragma once
#include "GameObject.h"
#include "CustomTypes.h"

class Player : public GameObject
{
private:
	Vector2D m_direction;
	Vector2D m_maxVelocity;
	Vector2D m_minVelocity;
	Vector2D m_velocity;

public:
	Player();
	~Player();
	void Update(float dt) override;
	void Draw(const sf::RenderWindow& w) override;
	void onKeyDown(KeyDownEvent evt) override;
	void onKeyUp(KeyUpEvent evt) override;
};

