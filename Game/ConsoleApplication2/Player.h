#pragma once
#include "GameObject.h"
#include "Constants.h"

using namespace std;


class Player : public GameObject
{
private:
	const float m_acceleration;
	sf::Vector2f m_direction;
	const float m_maxSpeed;
	sf::Vector2f m_position;
	sf::RectangleShape m_sprite;
	sf::Vector2f m_velocity;

	void updateVelocity(float dt);
	void calculateXVelocity(float acceleration);
	void calculateYVelocity(float acceleration);
	bool isSameDirection(float direction, float velocity);
	pair<bool, bool> shouldMove();
	void move(float dt);

public:
	Player();
	~Player();
	void Update(float dt) override;
	void Draw(sf::RenderWindow& w) override;
	void onKeyDown(KeyDownEvent evt) override;
	void onKeyUp(KeyUpEvent evt) override;
};

