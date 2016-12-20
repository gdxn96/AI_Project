#pragma once
#include <SFML\Graphics.hpp>

class GameObject
{
public:
	virtual void Update(float dt) = 0;
	virtual void Draw(sf::RenderWindow& w) = 0;

private:

};
