#pragma once
#include "GameObject.h"
#include "Constants.h"



class Player : public GameObject
{
private:
	const Vector2D m_acceleration;
	Vector2D m_direction;
	const Vector2D m_maxVelocity;
	Vector2D m_velocity;

	void updateVelocity(float dt);
	float calculateXVelocity(float dt);
	float calculateYVelocity(float dt);

public:
	Player();
	~Player();
	void Update(float dt) override;
	void Draw(const sf::RenderWindow& w) override;
	void onKeyDown(KeyDownEvent evt) override;
	void onKeyUp(KeyUpEvent evt) override;
};

