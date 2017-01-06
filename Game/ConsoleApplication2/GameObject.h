#pragma once

#include <SFML\Graphics.hpp>
#include "EventListener.h"


class GameObject : public EventListener
{
public:
	GameObject() {};
	virtual void Update(float dt) = 0;
	virtual void Draw(sf::RenderWindow& w) = 0;

private:
};
