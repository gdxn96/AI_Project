#pragma once

#include "Bullet.h"
#include "HealthObject.h"
#include "EventListener.h"
#include "AIManager.h"
#include "EntityFactory.h"
#include "CollisionManager.h"
#include "Mutant.h"
#include "Nest.h"

using namespace std;


class Player : public HealthObject, public EventListener
{
private:
	sf::RectangleShape m_shape;

	// Movement
	const Vector2D ACCELERATION;
	const Vector2D MAX_SPEED;
	Vector2D m_direction;
	Vector2D m_targetDirection;
	Vector2D m_facingDirection;
	Vector2D m_position;
	Vector2D m_speed;
	
	// Bullets
	int m_bulletsPerSecond;
	bool m_shooting;
	float m_timeTillNextShot;
	int NORMAL_FIRERATE;

	//-----------------------------------------
	// Power ups
	//-----------------------------------------
	// Hyperjump
	bool m_canHyperjump;
	// Smart bomb
	bool m_canUseSmartBomb;
	float BOMB_COOLDOWN;
	float m_timeTillBombActive;
	// Increased fire rate
	int MAX_FIRERATE;
	float m_timeTillIncreasedFireRateEnds;
	const int MAX_TIME_INCREASED_FIRE_RATE;
	// Invincibility
	const int MAX_INVINCIBILITY_TIME;
	float m_timeTillInvincibilityEnds;
	// EMP
	bool m_canUseEMP;
	//-----------------------------------------

	void UpdateDirection();
	void UpdateShootState(float dt);
	void UpdateSpeed(float dt);
	void UpdateSmartBomb(float dt);
	void UpdateIncreasedFireRate(float dt);
	void UpdateInvincibility(float dt);


public:
	Player(sf::Vector2f position, sf::Vector2f size, Vector2D acceleration, Vector2D maxSpeed);
	~Player();
	void InitializeEvents();
	void Update(float dt) override;
	void Draw(sf::RenderWindow& w) override;
	void DrawWithXOffset(sf::RenderWindow& window, float xOffset) override;
	void onGenericEvent(GenericEvent evt) override;
	void onKeyDown(KeyDownEvent evt) override;
	void onKeyUp(KeyUpEvent evt) override;
	void wrapPositions(Camera& cam) override;
	Vector2D getPosition();
	void addHyperJumpPowerUp();
	void increaseFireRate();
	void makeInvincible();
	bool isInvincible();
	void addEMP();
};

