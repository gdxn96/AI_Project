#include "stdafx.h"
#include "Game.h"

Game::Game()
{
	GameObject* player = new Player();
	InputManager* input = InputManager::getInstance();

	input->AddListener(static_cast<int>(EventListener::KeyDownEvent::UP), player);
	input->AddListener(static_cast<int>(EventListener::KeyDownEvent::LEFT), player);
	input->AddListener(static_cast<int>(EventListener::KeyDownEvent::DOWN), player);
	input->AddListener(static_cast<int>(EventListener::KeyDownEvent::RIGHT), player);
	input->AddListener(static_cast<int>(EventListener::KeyUpEvent::UP), player);
	input->AddListener(static_cast<int>(EventListener::KeyUpEvent::LEFT), player);
	input->AddListener(static_cast<int>(EventListener::KeyUpEvent::DOWN), player);
	input->AddListener(static_cast<int>(EventListener::KeyUpEvent::RIGHT), player);

	m_gameObjects.push_back(player);
}

void Game::Update(float dt)
{
	for (GameObject* gameObject : m_gameObjects)
	{
		gameObject->Update(dt);
	}
}

void Game::Draw(sf::RenderWindow& r)
{
	for (GameObject* gameObject : m_gameObjects)
	{
		gameObject->Draw(r);
	}
}