
#include "InputManager.h"
#include <iostream>
using namespace std;


InputManager* InputManager::m_instance = nullptr;

InputManager::InputManager() {}
InputManager::~InputManager() {}


InputManager* InputManager::getInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new InputManager();
	}

	return m_instance;
}


void InputManager::AddListener(EventListener::Event evt, EventListener* listener)
{
	// If listener not previously added...
	if (listeners.find(evt) == listeners.end())
	{
		listeners[evt] = new std::vector<EventListener*>();
	}

	listeners[evt]->push_back(listener);
}


void InputManager::Dispatch(EventListener::Event evt)
{
	if (listeners.find(evt) != listeners.end())
	{
		for (auto const &listener : *listeners[evt]) 
		{
			listener->onEvent(evt);
		}
	}
}


void InputManager::ProcessInput(sf::RenderWindow& window)
{
	sf::Event evt;

	// while event available for processing...
	while (window.pollEvent(evt))
	{
		if (evt.type == sf::Event::KeyPressed)
		{
			switch (evt.key.code)
			{
			case sf::Keyboard::Up:
				Dispatch(EventListener::Event::UPKEY_DOWN);
			case sf::Keyboard::Left:
				Dispatch(EventListener::Event::LEFTKEY_DOWN);
			case sf::Keyboard::Down:
				Dispatch(EventListener::Event::DOWNKEY_DOWN);
			case sf::Keyboard::Right:
				Dispatch(EventListener::Event::RIGHTKEY_DOWN);
			}
		}
		else if (evt.type == sf::Event::KeyReleased)
		{
			switch (evt.key.code)
			{
			case sf::Keyboard::Up:
				Dispatch(EventListener::Event::UPKEY_UP);
			case sf::Keyboard::Left:
				Dispatch(EventListener::Event::LEFTKEY_UP);
			case sf::Keyboard::Down:
				Dispatch(EventListener::Event::DOWNKEY_UP);
			case sf::Keyboard::Right:
				Dispatch(EventListener::Event::RIGHTKEY_UP);
			}
		}
	}
}
