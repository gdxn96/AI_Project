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
	m_gameView.setCenter(center);
}

Rect Camera::getViewPort()
{
	return Rect(m_gameView.getCenter() - sf::Vector2f(m_gameView.getSize().x / 2, m_gameView.getSize().y / 2), m_gameView.getSize());
}

void Camera::RenderObjects(sf::RenderWindow & window, std::vector<GameObject*>& m_gameObjects)
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
	window.setView(m_gameView);
	for (GameObject* gameObject : m_gameObjects)
	{
		gameObject->Draw(window);
		gameObject->DrawWithXOffset(window, m_levelSize.w);
	}
	window.setView(m_minimapView);
	for (GameObject* gameObject : m_gameObjects)
	{
		if (gameObject->IsMiniMapObject())
		{
			gameObject->Draw(window);
			gameObject->DrawWithXOffset(window, m_levelSize.w);
		}
	}
	renderCameraBounds(window);
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
