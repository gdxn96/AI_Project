#pragma once

#include "AIGameObject.h"
#include "AIManager.h"


class Astronaut : public AIGameObject
{
private:
	const int m_maxWanderTime; // in seconds
	float m_wanderTimeRemaining;
	sf::RectangleShape m_sprite;

public:
	Astronaut(Rect rectangle, bool isMiniMapObject);
	void Update(float dt) override;
	void Draw(sf::RenderWindow& w) override;
};