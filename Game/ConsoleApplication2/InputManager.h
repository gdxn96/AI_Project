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
	std::map<int, std::vector<EventListener*>*> listeners;

public:
	~InputManager();
	static InputManager* getInstance();
	void AddListener(int, EventListener*);
	void NukeListenerMap();
	void Dispatch(EventListener::KeyDownEvent);
	void Dispatch(EventListener::KeyUpEvent);
	void Dispatch(EventListener::GenericEvent);
	void ProcessInput(sf::RenderWindow* window);
};

