#pragma once
#include "GameObject.h"

class HealthObject : public GameObject
{
public:
	HealthObject(int maxHealth, sf::FloatRect bounds, bool isMinimapObject=false);
	virtual ~HealthObject() {};
	virtual void Damage(float damage);
private:
	float m_health;
};
