// ConsoleApplication2.cpp : Defines the entry point for the console application.
//


////Stick this in later
//mkdir "$(OutDir)images";
//mkdir "$(OutDir)audio";
//mkdir "$(OutDir)loadFiles";
//mkdir "$(OutDir)metadata";
//copy / y ".\images\*" "$(OutDir)images\";
//copy / y ".\audio\*" "$(OutDir)audio\";
//copy / y ".\loadFiles\*" "$(OutDir)loadFiles\";
//copy / y ".\metadata\*" "$(OutDir)metadata\";

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>

int main()
{
	srand(time(NULL));
	InputManager* input = InputManager::getInstance();
	Vector2D screenSize(1920, 1080);
	Vector2D levelSize(screenSize.w * 9, screenSize.h);
	sf::RenderWindow window(sf::VideoMode(screenSize.w, screenSize.h), "Defender");
	Game game = Game(screenSize, levelSize);
	const float FPS = 1.0f / 120;

	sf::Clock deltaClock; // used to calculate dt
	float dt = 0; // floating point dt as seconds
	
	while (window.isOpen())
	{
		if (dt > FPS)
		{
			deltaClock.restart();

			input->ProcessInput(&window);

			game.Update(dt);

			window.clear();

			//draw objects here
			game.Draw(window);

			window.display();
		}

		dt = deltaClock.getElapsedTime().asSeconds();
	}

	return 0;
}
