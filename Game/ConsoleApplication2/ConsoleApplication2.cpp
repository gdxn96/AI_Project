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
	Game game = Game();
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Defender");

	sf::Clock deltaClock; // used to calculate dt
	float dt = 0; // floating point dt as seconds

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		game.Update(dt);

		window.clear();

		//draw objects here
		game.Draw(window);

		window.display();

		dt = deltaClock.restart().asSeconds();
	}

	return 0;
}
