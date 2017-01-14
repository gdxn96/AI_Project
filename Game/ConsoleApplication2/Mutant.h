#pragma once
#include "GameObject.h"
#include "Boid.h"

class Mutant : public GameObject, public Boid
{
public:
	Mutant(Vector2D pos);
	Vector2D getPosition();
	Vector2D getVelocity();
	bool isPredator();
private:

};
