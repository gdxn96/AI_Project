#pragma once
#include <SFML\Graphics.hpp>

class GameObject
{
public:
	GameObject();
	virtual void Update(float dt) = 0;
	virtual void Draw(const sf::RenderWindow& w) = 0;

private:

};
