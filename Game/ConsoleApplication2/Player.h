#pragma once

#include "Bullet.h"
#include "AIGameObject.h"
#include "EventListener.h"

using namespace std;


class Player : public AIGameObject, public EventListener
{
private:
	Vector2D m_targetDirection;
	Vector2D m_facingDirection;
	Vector2D m_position;
	
	sf::RectangleShape m_shape;

	vector<Bullet*> m_bullets;
	int m_bulletsPerSecond;
	bool m_shooting;
	float m_timeTillNextShot;

	void UpdateBullets(float dt);
	void UpdateDirection();
	void UpdateShootState(float dt);
	void UpdateSpeed(float dt);


public:
	Player(Vector2D pos, Vector2D accel, Vector2D maxSpeed, bool isMiniMapObject);
	~Player();
	void Update(float dt) override;
	void Draw(sf::RenderWindow& w) override;
	void DrawWithXOffset(sf::RenderWindow& window, float xOffset) override;
	void onGenericEvent(GenericEvent evt) override;
	void onKeyDown(KeyDownEvent evt) override;
	void onKeyUp(KeyUpEvent evt) override;
	void wrapPositions(Camera& cam) override;
};

