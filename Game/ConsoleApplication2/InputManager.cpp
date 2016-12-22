#include "stdafx.h"
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



void InputManager::AddListener(int evt, EventListener* listener)
{
	// If listener not previously added...
	if (listeners.find(evt) == listeners.end())
	{
		listeners[evt] = new std::vector<EventListener*>();
	}

	listeners[evt]->push_back(listener);
}



void InputManager::Dispatch(EventListener::KeyDownEvent evt)
{
	int evtAsInt = static_cast<int>(evt);

	if (listeners.find(evtAsInt) != listeners.end())
	{
		for (auto const &listener : *listeners[evtAsInt])
		{
			listener->onEvent(evt);
		}
	}
}

void InputManager::Dispatch(EventListener::KeyUpEvent evt)
{
	int evtAsInt = static_cast<int>(evt);

	if (listeners.find(evtAsInt) != listeners.end())
	{
		for (auto const &listener : *listeners[evtAsInt])
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
				Dispatch(EventListener::KeyDownEvent::UP);
			case sf::Keyboard::Left:
				Dispatch(EventListener::KeyDownEvent::LEFT);
			case sf::Keyboard::Down:
				Dispatch(EventListener::KeyDownEvent::DOWN);
			case sf::Keyboard::Right:
				Dispatch(EventListener::KeyDownEvent::RIGHT);
			}
		}
		else if (evt.type == sf::Event::KeyReleased)
		{
			switch (evt.key.code)
			{
			case sf::Keyboard::Up:
				Dispatch(EventListener::KeyUpEvent::UP);
			case sf::Keyboard::Left:
				Dispatch(EventListener::KeyUpEvent::LEFT);
			case sf::Keyboard::Down:
				Dispatch(EventListener::KeyUpEvent::DOWN);
			case sf::Keyboard::Right:
				Dispatch(EventListener::KeyUpEvent::RIGHT);
			}
		}
	}
}
