#pragma once

class Damageable
{
public:
	Damageable(float damage) : m_damage(damage)
	{
	}

	virtual ~Damageable()
	{
	}

	float getDamage()
	{
		return m_damage;
	}

private:
	float m_damage;
};
