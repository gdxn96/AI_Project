#pragma once
#include <SFML\Graphics.hpp>
#include "SimpleTypes.h"

class GameObject
{
public:
	GameObject(bool isMiniMapObject = false, sf::FloatRect bounds = sf::FloatRect()) : m_bounds(bounds), m_isMinimapObject(isMiniMapObject) {};
	virtual void Update(float dt) = 0;
	virtual void Draw(sf::RenderWindow& w) = 0;
	virtual void DrawWithXOffset(sf::RenderWindow& window, float xOffset) = 0;
	virtual bool IsMiniMapObject() { return m_isMinimapObject; };
	virtual sf::FloatRect getAABB() { return m_bounds; };
	virtual sf::FloatRect getAABBWithXOffset(float xOffset) { sf::FloatRect r = m_bounds; r.left += xOffset; return r; };
	virtual void setBounds(sf::FloatRect bounds) { m_bounds = bounds; };

protected:
	bool m_isMinimapObject;
	sf::FloatRect m_bounds;
};
