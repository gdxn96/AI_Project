#pragma once
#include <vector>
#include "GameObject.h"

class GameObject;

class Camera
{
public:
	Camera(Vector2D screenSize, Vector2D levelSize);
	void Move(sf::Vector2f moveAmount);
	void SetCenter(sf::Vector2f center);
	sf::FloatRect getViewPort(sf::View& v);
	void RenderObjects(sf::RenderWindow& window, std::vector<GameObject*>& m_gameObjects);
	void UpdateView();
	void RenderView(sf::RenderWindow & window, sf::View & view, std::vector<GameObject*>& objects);
	bool isAABBInViewport(sf::FloatRect AABB, sf::FloatRect viewport);
	void Wrap(Vector2D& position);
	void Wrap(sf::FloatRect& bounds);
	std::vector<GameObject*> getObjectsInViewPort(std::vector<GameObject*> objects);

private:
	void renderCameraBounds(sf::RenderWindow& window);
	sf::View m_minimapView, m_gameView;
	Vector2D m_screenSize, m_levelSize;
};
