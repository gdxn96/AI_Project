#pragma once
#include "GameObject.h"
#include "AIManager.h"
#include "DamageObject.h"

class Bullet : public GameObject, public Damageable
{
private:
	Vector2D m_velocity;
	Vector2D m_position;
	sf::RectangleShape m_shape;
	float m_timeToLive;


public:
	Bullet(Vector2D pos, Vector2D dir);
	~Bullet();
	void Update(float dt) override;
	void wrapPositions(Camera & cam) override;
	void Draw(sf::RenderWindow& w) override;
	void DrawWithXOffset(sf::RenderWindow& window, float xOffset) override;
};