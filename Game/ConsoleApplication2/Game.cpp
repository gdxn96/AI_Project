#include "stdafx.h"
#include "Game.h"

Game::Game(Vector2D screenSize, Vector2D levelSize) : 
	m_screenSize(screenSize),
	m_levelSize(levelSize), 
	m_camera(screenSize, levelSize)
{
	m_gameObjects.push_back(new Terrain(screenSize.h * 7.f / 10, screenSize.h * 8.f / 10, screenSize));
}

void Game::Update(float dt)
{
	for (GameObject* gameObject : m_gameObjects)
	{
		gameObject->Update(dt);
	}
}

void Game::Draw(sf::RenderWindow & r)
{
	m_camera.RenderObjects(r, m_gameObjects);
}
