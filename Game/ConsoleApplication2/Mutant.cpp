#include "stdafx.h"
#include "Mutant.h"

Mutant::Mutant(Vector2D pos) : Boid(false), GameObject(sf::FloatRect(pos.x, pos.y, 20, 20))
{
}

Vector2D Mutant::getPosition()
{
	return Vector2D();
}

Vector2D Mutant::getVelocity()
{
	return Vector2D();
}

bool Mutant::isPredator()
{
	return false;
}
