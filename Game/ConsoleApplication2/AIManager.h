#pragma once

#include "Astronaut.h"
#include "Player.h"
#include <vector>

class Player;
class Astronaut;

using namespace std;


class AIManager
{
public:
	static void initialize(sf::FloatRect levelBounds);

	static void registerPlayer(Player* player);
	static void registerAstronaut(Astronaut* astronaut);

	static void unregisterPlayer();
	static void unregisterAstronaut(Astronaut* astronaut);

	static Vector2D getPlayerPos();
	static Vector2D getClosestAstronautPos(Vector2D position);

	static void wander(float dt, float& timeRemaining, int maxTime, Vector2D& direction, bool horizontalOnly = false);
	static void seekToward(Vector2D position, Vector2D targetPosition, Vector2D& direction);
	static void evadeFrom(Vector2D position, Vector2D targetPosition, Vector2D& direction);
	static void flock();

private:
	static Player* m_player;
	static vector<Astronaut*> m_astronauts;
	static sf::FloatRect m_levelBounds;
};