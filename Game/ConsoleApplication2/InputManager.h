#pragma once

#include<map>
#include<vector>
#include <SFML\Graphics.hpp>
#include "EventListener.h"


class InputManager
{
private:
	InputManager();
	static InputManager* m_instance;
	std::map<EventListener::Event, std::vector<EventListener*>*> listeners;

public:
	~InputManager();
	static InputManager* getInstance();
	void AddListener(EventListener::KeyDownEvent, EventListener*);
	void AddListener(EventListener::KeyUpEvent, EventListener*);
	void AddListener(EventListener::GenericEvent, EventListener*);
	void Dispatch(EventListener::Event);
	void ProcessInput(sf::RenderWindow& window);
};

