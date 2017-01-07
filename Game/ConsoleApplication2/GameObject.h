#pragma once
#include <SFML\Graphics.hpp>
#include "SimpleTypes.h"
#include "EventListener.h"

class GameObject : public EventListener
{
public:
	GameObject(Rect bounds = Rect(), bool isMiniMapObject = false)
		: m_bounds(bounds),
		m_isMinimapObject(isMiniMapObject) {}

	GameObject(bool isMiniMapObject = false, Rect bounds = Rect())
		: m_bounds(bounds),
		m_isMinimapObject(isMiniMapObject) {}

	virtual void Update(float dt) = 0;
	virtual void Draw(sf::RenderWindow& w) = 0;
	virtual bool IsMiniMapObject() { return m_isMinimapObject; };
	virtual Rect getAABB() { return m_bounds; };
	virtual void setBounds(Rect bounds) { m_bounds = bounds; };

protected:
	bool m_isMinimapObject;
	Rect m_bounds;
};