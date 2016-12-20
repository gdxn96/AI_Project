#include "stdafx.h"
#include "Game.h"

Game::Game()
{
	m_gameObjects.push_back(new Terrain(500, 1920));
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
	for (GameObject* gameObject : m_gameObjects)
	{
		gameObject->Draw(r);
	}
}
