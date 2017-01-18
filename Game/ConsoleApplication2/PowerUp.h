#pragma once

#include "Vector2D.h"
#include "GameObject.h"
#include "PowerUpTypes.h"


class PowerUp: public GameObject
{
public:
	PowerUp(int type, sf::Vector2f position, sf::Vector2f size);
	~PowerUp();
	void initializeColor();
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void DrawWithXOffset(sf::RenderWindow& window, float xOffset) override;

private:
	sf::FloatRect m_bounds;
	sf::Color m_color;
	Vector2D m_position;
	sf::RectangleShape m_shape;
	float m_timeToLive;
	int m_type;
};