#pragma once
#include <SFML\Graphics.hpp>

class GameObject
{
public:
	GameObject();
	virtual void Update(float dt) = 0;
	virtual void Draw(sf::RenderWindow) = 0;

private:

};
