#pragma once
#include <SFML\Graphics.hpp>
#include "SimpleTypes.h"

class GameObject
{
public:
	GameObject(bool isMiniMapObject = false, Rect bounds = Rect()) : m_bounds(bounds), m_isMinimapObject(isMiniMapObject) {};
	virtual void Update(float dt) = 0;
	virtual void Draw(sf::RenderWindow& w) = 0;
	virtual void DrawWithXOffset(sf::RenderWindow& window, float xOffset) = 0;
	virtual bool IsMiniMapObject() { return m_isMinimapObject; };
	virtual Rect getAABB() { return m_bounds; };
	virtual Rect getAABBWithXOffset(float xOffset) { return m_bounds + Rect(xOffset); };
	virtual void setBounds(Rect bounds) { m_bounds = bounds; };

protected:
	bool m_isMinimapObject;
	Rect m_bounds;
};
