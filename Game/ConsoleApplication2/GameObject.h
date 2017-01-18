#pragma once
#include <SFML\Graphics.hpp>
#include "SimpleTypes.h"
#include "Camera.h"
#include "PhysicsManager.h"
#include <iostream>
#include "AssetLoader.h"

class Camera;
class GameObject
{
private:
	bool m_alive;

public:
	GameObject(sf::FloatRect bounds, bool isMiniMapObject = false)
		: m_isMinimapObject(isMiniMapObject),
		  m_bounds(bounds),
		  m_alive(true){};

	virtual ~GameObject() {};

	virtual void Update(float dt) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;
	virtual void DrawWithXOffset(sf::RenderWindow& window, float xOffset) = 0;
	virtual bool IsMiniMapObject() { return m_isMinimapObject; };
	virtual sf::FloatRect getAABB() { return m_bounds; };
	virtual sf::FloatRect getAABBWithXOffset(float xOffset) { sf::FloatRect r = m_bounds; r.left += xOffset; return r; };
	virtual void setBounds(sf::FloatRect bounds) { m_bounds = bounds; };
	virtual void wrapPositions(Camera& cam);
	virtual void Damage(float _) {};

	void kill() { m_alive = false; }
	bool isAlive() { return m_alive; }

protected:
	bool m_isMinimapObject;
	sf::FloatRect m_bounds;
};
