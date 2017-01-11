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

int main()
{
	srand(time(NULL));
	InputManager* input = InputManager::getInstance();
	Vector2D screenSize(1920, 1080);
	Vector2D levelSize(screenSize.w * 9, screenSize.h);
	sf::RenderWindow window(sf::VideoMode(screenSize.w, screenSize.h), "Defender");
	Game game = Game(screenSize, levelSize);

	sf::Clock deltaClock; // used to calculate dt
	float dt = 0; // floating point dt as seconds
	
	while (window.isOpen())
	{
		/*sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}*/

		input->ProcessInput(&window);
		game.Update(dt);
		window.clear();
		game.Draw(window);
		window.display();

		dt = deltaClock.restart().asSeconds();
	}

	return 0;
}
