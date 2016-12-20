#include "stdafx.h"
#include "Game.h"

Game::Game()
{
}

void Game::Update(float dt)
{
	for (auto& gameObject : m_gameObjects)
	{
		gameObject->Update(dt);
	}
}

void Game::Draw(sf::RenderWindow & r)
{
	for (auto& gameObject : m_gameObjects)
	{
		gameObject->Draw(r);
	}
}
