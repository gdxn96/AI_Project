#pragma once

#include "Constants.h"
#include "Bullet.h"
#include "AIGameObject.h"

using namespace std;


class Player : public AIGameObject
{
private:
	Vector2D m_targetDirection;
	Vector2D m_facingDirection;

	vector<Bullet*> m_bullets;
	int m_bulletsPerSecond;
	bool m_shooting;
	float m_timeTillNextShot;

	void UpdateBullets(float dt);
	void UpdateDirection();
	void UpdateShootState(float dt);
	void UpdateSpeed(float dt);


public:
	Player(Rect bounds, Vector2D accel, Vector2D maxSpeed, bool isMiniMapObject);
	~Player();
	void Update(float dt) override;
	void Draw(sf::RenderWindow& w) override;
	void onGenericEvent(GenericEvent evt) override;
	void onKeyDown(KeyDownEvent evt) override;
	void onKeyUp(KeyUpEvent evt) override;
};

