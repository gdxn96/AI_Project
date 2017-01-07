#pragma once

#include "Constants.h"
#include "Bullet.h"

using namespace std;


class Player : public MovingGameObject
{
private:
	sf::Vector2f m_targetDirection;
	sf::Vector2f m_facingDirection;

	vector<Bullet*> m_bullets;
	int m_bulletsPerSecond;
	bool m_shooting;
	float m_timeTillNextShot;

	void UpdateDirection();
	void UpdateShootState(float dt);
	void UpdateSpeed(float dt);


public:
	Player(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f accel, sf::Vector2f maxSpeed);
	~Player();
	void Update(float dt) override;
	void Draw(sf::RenderWindow& w) override;
	void onGenericEvent(GenericEvent evt) override;
	void onKeyDown(KeyDownEvent evt) override;
	void onKeyUp(KeyUpEvent evt) override;
};

