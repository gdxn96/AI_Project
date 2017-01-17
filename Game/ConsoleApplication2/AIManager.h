#pragma once

#include "Vector2D.h"
#include "GameObject.h"
#include "Boid.h"
#include "Astronaut.h"
#include "Player.h"
#include "Abductor.h"
#include <vector>
class Player;
class Astronaut;
class Boid;
class Abductor;

class AIManager
{
public:
	static Vector2D Separation(std::vector<Boid*> flockObjects, Vector2D & position, Vector2D & velocity, const float maxSpeed, const float maxAcceleration, bool predator = false);
	static Vector2D Alignment(std::vector<Boid*> flockObjects, Vector2D & position, Vector2D & velocity, const float maxSpeed, const float maxAcceleration);
	static Vector2D Cohesion(std::vector<Boid*> flockObjects, Vector2D & position, Vector2D & velocity, Vector2D & acceleration, const float maxSpeed, const float maxAcceleration);
	static Vector2D seek(Vector2D target, Vector2D & velocity, Vector2D & acceleration, const float maxSpeed, const float maxAcceleration);
	static void flock(Boid * b, Vector2D & acceleration, Vector2D & position, Vector2D & velocity, const float maxSpeed, const float maxAcceleration, bool predator=false);
	static void swarm(Boid * b, Vector2D position, Vector2D & acceleration);

	static void process();

	static void registerPlayer(Player* player);
	static void registerAstronaut(Astronaut* astronaut);

	static void registerSwarmBoid(Boid* b);
	static void registerFlockBoid(Boid* b);

	static void unregisterBoid(Boid* b);

	static void unregisterPlayer();
	static void unregisterAstronaut(Astronaut* astronaut);

	static Vector2D getPlayerPos();
	static Vector2D getClosestPlayerPos(Vector2D pos);
	static Vector2D getClosestAstronautPos(Vector2D position);

	static void wander(float dt, float& timeRemaining, int maxTime, Vector2D& direction, bool horizontalOnly = false);
	static void wanderThrust(float dt, float& timeUntilDecelerate, float MAXTIME, Vector2D& velocity, Vector2D& acceleration, const float MAX_ACCEL);
	static void seekToward(Vector2D position, Vector2D targetPosition, Vector2D& direction);
	static void evadeFrom(Vector2D position, Vector2D targetPosition, Vector2D& direction);
	static void avoid(Vector2D position, Vector2D targetPosition, Vector2D& acceleration, const float maxAccel);

private:
	static Player* m_player;
	static std::vector<Astronaut*> m_astronauts;
	static std::vector<Boid*> m_swarmObjects;
	static std::vector<Boid*> m_flockObjects;
	static std::vector<Abductor*> m_abductors;
};