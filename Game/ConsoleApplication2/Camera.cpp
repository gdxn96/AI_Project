#include "stdafx.h"
#include "Camera.h"

Camera::Camera(Vector2D screenSize, Vector2D levelSize) : 
	m_screenSize(screenSize),
	m_levelSize(levelSize), 
	m_minimapView(sf::FloatRect(0, 0, levelSize.w, levelSize.h)), 
	m_gameView(sf::FloatRect(0, 0, screenSize.w, screenSize.h))
{
	m_gameView.setViewport(sf::FloatRect(0, 0, 1, 1)); //percentages
	m_minimapView.setViewport(sf::FloatRect(0.2f, 0, 0.6f, 0.1f)); //percentages
}

void Camera::Move(sf::Vector2f moveAmount)
{
	m_gameView.move(moveAmount);
}

void Camera::SetCenter(sf::Vector2f center)
{
	center.y = m_levelSize.h / 2;
	m_gameView.setCenter(center);
}

sf::FloatRect Camera::getViewPort(sf::View& v)
{
	return sf::FloatRect(v.getCenter() - sf::Vector2f(v.getSize().x / 2, v.getSize().y / 2), v.getSize());
}

void Camera::RenderObjects(sf::RenderWindow & window, std::vector<GameObject*>& gameObjects)
{
	UpdateView();
	RenderView(window, m_gameView, gameObjects);
	RenderView(window, m_minimapView, gameObjects);
	renderCameraBounds(window);
}

void Camera::UpdateView()
{
	if (m_gameView.getCenter().x > m_levelSize.w * 1.5f)
	{
		m_gameView.move(sf::Vector2f(-m_levelSize.w, 0));
	}

	if (m_gameView.getCenter().x < m_levelSize.w * 0.5f)
	{
		m_gameView.move(sf::Vector2f(m_levelSize.w, 0));
	}

	m_minimapView.setCenter(m_gameView.getCenter());
}

void Camera::RenderView(sf::RenderWindow& window, sf::View& view, std::vector<GameObject*>& objects)
{
	window.setView(view);
	sf::FloatRect viewport = getViewPort(view);

	for (GameObject* object : objects)
	{
		sf::FloatRect objectAABB = object->getAABB();
		sf::FloatRect objectOffsetAABB = objectAABB;
		objectOffsetAABB.left += m_levelSize.width;

		if (isAABBInViewport(objectAABB, viewport))
		{
			object->Draw(window);
		}

		if (isAABBInViewport(objectOffsetAABB, viewport))
		{
			object->DrawWithXOffset(window, m_levelSize.width);
		}
	}
}

bool Camera::isAABBInViewport(sf::FloatRect AABB, sf::FloatRect viewport)
{
	return (AABB.left > viewport.left && AABB.left < viewport.left + viewport.width) ||
		   (AABB.left + AABB.width > viewport.left && AABB.left + AABB.width < viewport.left + viewport.width);
}

void Camera::Wrap(Vector2D& position)
{
	if (position.x > m_levelSize.w)
	{
		position.x -= m_levelSize.w;
	}
	else if (position.x < 0)
	{
		position.x += m_levelSize.w;
	}
}

void Camera::Wrap(sf::FloatRect & bounds)
{
	if (bounds.left > m_levelSize.w)
	{
		bounds.left -= m_levelSize.w;
	}
	else if (bounds.left < m_levelSize.w)
	{
		bounds.left += m_levelSize.w;
	}
}

void Camera::renderCameraBounds(sf::RenderWindow& window)
{
	sf::Vector2f offset(40, 40);
	sf::RectangleShape rect = sf::RectangleShape(m_gameView.getSize() - offset);
	rect.setPosition(m_gameView.getCenter() - sf::Vector2f((m_gameView.getSize().x / 2) - offset.x / 2, (m_gameView.getSize().y / 2) - offset.y / 2));
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineColor(sf::Color::White);
	rect.setOutlineThickness(20);
	window.draw(rect);
}


std::vector<GameObject*> Camera::getObjectsInViewPort(std::vector<GameObject*> objects)
{
	std::vector<GameObject*> results;
	sf::FloatRect viewport = getViewPort(m_gameView);
	//draw game objects
	for (GameObject* gameObject : objects)
	{
		//cull objects not in view
		sf::FloatRect objectAABB = gameObject->getAABB();
		if ((objectAABB.left > viewport.left && objectAABB.left < viewport.left + viewport.width) ||
			(objectAABB.left + objectAABB.width > viewport.left && objectAABB.left + objectAABB.width < viewport.left + viewport.width))
		{
			results.push_back(gameObject);
		}
		else if (objectAABB.left + m_levelSize.w > viewport.left && objectAABB.left + m_levelSize.w < viewport.left + viewport.width ||
			(objectAABB.left + objectAABB.width + m_levelSize.w > viewport.left && objectAABB.left + objectAABB.width + m_levelSize.w < viewport.left + viewport.width))
		{
			results.push_back(gameObject);
		}
	}

	return results;
}