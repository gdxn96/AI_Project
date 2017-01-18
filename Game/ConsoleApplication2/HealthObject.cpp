#include "stdafx.h"
#include "HealthObject.h"

HealthObject::HealthObject(int maxHealth, sf::FloatRect bounds, bool isMinimapObject) : GameObject(bounds, isMinimapObject), m_health(maxHealth)
{
}

void HealthObject::Damage(float damage)
{
    m_health -= damage;
	if (m_health < 0)
	{
		this->kill();
	}
}
