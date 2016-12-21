#pragma once
#include <vector>
#include "GameObject.h"

class Camera
{
public:
	Camera(Vector2D screenSize, Vector2D levelSize);
	void Move(sf::Vector2f moveAmount);
	void SetCenter(sf::Vector2f center);
	Rect getViewPort();
	void RenderObjects(sf::RenderWindow& window, std::vector<GameObject*>& m_gameObjects);
private:
	void renderCameraBounds(sf::RenderWindow& window);
	sf::View m_minimapView, m_gameView;
};
