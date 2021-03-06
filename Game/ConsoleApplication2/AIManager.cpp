#include "stdafx.h"
#include "AIManager.h"
#include <limits.h>
#include <algorithm>


Player* AIManager::m_player = nullptr;
vector<Astronaut*> AIManager::m_astronauts;
std::vector<Boid*> AIManager::m_swarmObjects;
std::vector<Boid*> AIManager::m_flockObjects;
std::vector<Abductor*> AIManager::m_abductors;
std::vector<Meteor*> AIManager::m_meteors;
sf::FloatRect AIManager::m_levelBounds = sf::FloatRect();

void AIManager::wanderThrust(float dt, float& timeUntilDecelerate, float MAXTIME, Vector2D& velocity, Vector2D& acceleration, const float MAX_ACCEL)
{
	timeUntilDecelerate -= dt;
	Vector2D direction;
	float mag;

	if (timeUntilDecelerate <= 0)
	{
		acceleration = (0,0);

		if (velocity.Magnitude() <= 50)
		{
			timeUntilDecelerate = MAXTIME;
			mag = RandomFloat(MAX_ACCEL * .5f, MAX_ACCEL);
			direction = Vector2D(RandomFloat(0, 2 * 3.14));
			acceleration += direction * mag;
		}
	}
}

Vector2D AIManager::getClosestPlayerPos(Vector2D pos)
{
	Vector2D caseA, caseB, caseC;
	caseA = m_player->getPosition();
	caseB = caseA + Vector2D(1920*9,0);
	caseC = caseA - Vector2D(1920 * 9, 0);

	float distA = Vector2D::DistanceSq(pos, caseA);
	float distB = Vector2D::DistanceSq(pos, caseB);
	float distC = Vector2D::DistanceSq(pos, caseC);

	if (distA < distB && distA < distC)
	{
		return caseA;
	}
	else if (distB < distC && distB < distA)
	{
		return caseB;
	}
	else
	{
		return caseC;
	}
}


void AIManager::initialize(sf::FloatRect levelBounds)
{
	m_levelBounds = levelBounds;
}

void AIManager::registerPlayer(Player* player)
{
	m_player = player;
}

void AIManager::registerAbductor(Abductor* abductor)
{
	m_abductors.push_back(abductor);
}

void AIManager::registerAstronaut(Astronaut* astronaut)
{
	m_astronauts.push_back(astronaut);
}

void AIManager::registerMeteor(Meteor * m)
{
	m_meteors.push_back(m);
}

void AIManager::unregisterMeteor(Meteor * m)
{
	m_meteors.erase(std::remove(m_meteors.begin(), m_meteors.end(), m), m_meteors.end());
}

void AIManager::registerSwarmBoid(Boid * b)
{
	m_swarmObjects.push_back(b);
}

void AIManager::registerFlockBoid(Boid * b)
{
	m_flockObjects.push_back(b);
}

void AIManager::unregisterBoid(Boid * b)
{
	m_flockObjects.erase(std::remove(m_flockObjects.begin(), m_flockObjects.end(), b), m_flockObjects.end());
	m_abductors.erase(std::remove(m_abductors.begin(), m_abductors.end(), b), m_abductors.end());
	m_swarmObjects.erase(std::remove(m_swarmObjects.begin(), m_swarmObjects.end(), b), m_swarmObjects.end());
}


void AIManager::unregisterPlayer()
{
	m_player = nullptr;
}

void AIManager::unregisterAstronaut(Astronaut* astronaut)
{
	std::remove(m_astronauts.begin(), m_astronauts.end(), astronaut);
}

void AIManager::avoidObstacles(Vector2D position, Vector2D & acceleration, const float MAX_ACCEL)
{
	for (Meteor* m : m_meteors)
	{
		if (Vector2D::Distance(m->getPosition(), position) < 100)
		{
			float disSq = Vector2D::DistanceSq(position, m->getPosition());
			Vector2D x = (position - m->getPosition()).Normalize();
			acceleration += x * std::min(0.8f * disSq, MAX_ACCEL);
		}
	}
}

Vector2D AIManager::getPlayerPos()
{
	return m_player->getPosition();
}


void AIManager::wander(float dt, float& timeRemaining, int maxTime, Vector2D& direction)
{
	timeRemaining -= dt;

	if (timeRemaining <= 0)
	{
		timeRemaining = rand() % (maxTime + 1);
		direction = Vector2D(RandomFloat(0, 2 * 3.14));
	}
}

void AIManager::wanderHorizontal(float dt, float& timeRemaining, int maxTime, Vector2D& direction)
{
	timeRemaining -= dt;

	if (timeRemaining <= 0)
	{
		timeRemaining = rand() % (maxTime + 1);
		direction.x = rand() & true ? 1 : -1;
	}
}

void AIManager::seekToward(Vector2D position, Vector2D targetPosition, Vector2D& direction)
{
	direction = targetPosition - position;
	direction = direction.Normalize();
}

void AIManager::evadeFrom(Vector2D position, Vector2D targetPosition, Vector2D& direction)
{
	direction = position - targetPosition;
	direction = direction.Normalize();
}

// Function that checks and modifies the distance
// of a Boid if it breaks the law of separation.
Vector2D AIManager::Separation(std::vector<Boid*> flockObjects, Vector2D& position, Vector2D& velocity, const float maxSpeed, const float maxAcceleration, bool predator)
{
	// If the Boid we're looking at is a predator, do not run the separation
	// algorithm

	// Distance of field of vision for separation between flockObjects
	float desiredseparation = 20;

	Vector2D steer(0, 0);
	int count = 0;
	// For every game object in the system, check if it's too close
	for (int i = 0; i < flockObjects.size(); i++)
	{
		// Calculate distance from current game object to game object we're looking at
		float d = position.Distance(flockObjects[i]->getPosition(), position);
		// If this is a fellow game object and it's too close, move away from it
		if ((d > 0) && (d < desiredseparation))
		{
			Vector2D diff(0, 0);
			diff = position - flockObjects[i]->getPosition();
			diff = diff.Normalize();
			diff = diff / d;      // Weight by distance
			steer += diff;
			count++;
		}
		// If current game object is a predator and the game object we're looking at is also
		// a predator, then separate only slightly 
		if ((d > 0) && (d < desiredseparation) && predator == true && flockObjects[i]->isPredator() == true)
		{
			Vector2D pred2pred(0, 0);
			pred2pred = position - flockObjects[i]->getPosition();
			pred2pred = pred2pred.Normalize();
			pred2pred = pred2pred / d;
			steer += pred2pred;
			count++;
		}

		// If current game object is not a predator, but the game object we're looking at is
		// a predator, then create a large separation Vector2D
		else if ((d > 0) && (d < desiredseparation + 70) && flockObjects[i]->isPredator() == true)
		{
			Vector2D pred(0, 0);
			pred = position - flockObjects[i]->getPosition();
			pred = pred * 900;
			steer += pred;
			count++;
		}
	}
	// Adds average difference of location to acceleration
	if (count > 0)
	{
		steer = steer / count;
	}
	if (steer.Magnitude() > 0)
	{
		// Steering = Desired - Velocity
		steer = steer.Normalize();
		steer = steer * maxSpeed;
		steer = steer - velocity;
		steer.limit(maxAcceleration);
	}
	return steer;
}

// Alignment calculates the average velocity in the field of view and 
// manipulates the velocity of the Boid passed as parameter to adjust to that
// of nearby flockObjects.
Vector2D AIManager::Alignment(std::vector<Boid*> flockObjects, Vector2D& position, Vector2D& velocity, const float maxSpeed, const float maxAcceleration)
{
	// If the Boid we're looking at is a predator, do not run the alignment
	// algorithm
	//if (predator == true) 
	//	return Vector2D(0,0);
	float neighbordist = 50;

	Vector2D sum(0, 0);
	int count = 0;
	for (int i = 0; i < flockObjects.size(); i++)
	{
		float d = position.Distance(flockObjects[i]->getPosition(), position);
		if ((d > 0) && (d < neighbordist)) // 0 < d < 50
		{
			sum += flockObjects[i]->getVelocity();
			count++;
		}
	}
	// If there are flockObjects close enough for alignment...
	if (count > 0) 
	{
		sum = sum / (float)count;// Divide sum by the number of close flockObjects (average of velocity)
		sum = sum.Normalize();	   		// Turn sum into a unit vector, and
		sum = sum * maxSpeed;    // Multiply by maxSpeed
								 // Steer = Desired - Velocity
		Vector2D steer;
		steer = sum - velocity; //sum = desired(average)  
		steer.limit(maxAcceleration);
		return steer;
	}
	else {
		Vector2D temp(0, 0);
		return temp;
	}
}

// Cohesion finds the average location of nearby flockObjects and manipulates the 
// steering force to move in that direction.
Vector2D AIManager::Cohesion(std::vector<Boid*> flockObjects, Vector2D& position, Vector2D& velocity, Vector2D& acceleration, const float maxSpeed, const float maxAcceleration)
{
	// If the game object we're looking at is a predator, do not run the cohesion
	// algorithm
	//if (predator == true)
	//	return Vector2D(0,0);

	float neighbordist = 50;

	Vector2D sum(0, 0);
	int count = 0;
	for (int i = 0; i < flockObjects.size(); i++)
	{
		float d = position.Distance(flockObjects[i]->getPosition(), position);
		if ((d > 0) && (d < neighbordist))
		{
			sum += flockObjects[i]->getPosition();
			count++;
		}
	}
	if (count > 0)
	{
		sum = sum / count;
		return seek(sum, velocity, acceleration, maxSpeed, maxAcceleration);
	}
	else {
		Vector2D temp(0, 0);
		return temp;
	}
}

// Seek function limits the maxSpeed, finds necessary steering force and
// normalizes the vectors.
Vector2D AIManager::seek(Vector2D targetPos, Vector2D& velocity, Vector2D& acceleration, const float maxSpeed, const float maxAcceleration)
{
	Vector2D desired;
	desired = -targetPos;  // A vector pointing from the location to the target
						// Normalize desired and scale to maximum speed
	desired = desired.Normalize();
	desired = desired * maxSpeed;

	// Steering = Desired minus Velocity
	acceleration = desired - velocity;
	acceleration.limit(maxAcceleration);  // Limit to maximum steering force
	return acceleration;
}

//Applies all three laws for the flock of flockObjects and modifies to keep them from
//breaking the laws.
void AIManager::flock(Boid* b, Vector2D& acceleration, Vector2D& position, Vector2D& velocity, const float maxSpeed, const float maxAcceleration, bool predator)
{
	std::vector<Boid*> v;
	for (Boid* n : m_flockObjects)
	{
		if (b->getPosition().Distance(n->getPosition(), b->getPosition()) < 500)
		{
			v.push_back(n);
		}
	}
	Vector2D sep = Separation(v, position, velocity, maxSpeed, maxAcceleration, predator);
	Vector2D ali = Alignment(v, position, velocity, maxSpeed, maxAcceleration);
	Vector2D coh = Cohesion(v, position, velocity, acceleration, maxSpeed, maxAcceleration);

	// Arbitrarily weight these forces
	sep * 1.5;
	ali * 1.0; // Might need to alter weights for different characteristics
	coh * 1.0;

	// Add the force vectors to acceleration
	acceleration += sep + ali + coh;
}

void AIManager::swarm(Boid * b, Vector2D position, Vector2D& acceleration)
{
	/*		Lenard-Jones Potential function
	Vector R = me.position - you.position
	Real D = R.magnitude()
	Real U = -A / pow(D, N) + B / pow(D, M)
	R.normalise()
	force = force + R*U
	*/

	std::vector<Boid*> v;
	for (Boid* n : m_swarmObjects)
	{
		if (b->getPosition().Distance(n->getPosition(), b->getPosition()) < 500)
		{
			v.push_back(n);
		}
	}

	float A = 0.1f;
	float B = 0.8f;
	float N = 0.4f;
	float M = 0.8f;
	float D;
	float U = 0;
	Vector2D R;
	Vector2D sum(0, 0);

	for (int i = 0; i < v.size(); i++)
	{
		U = 0;
		R = position - v[i]->getPosition();
		D = R.Magnitude();
		if (D != 0)
		{
			U = (-A / pow(D, N)) + (B / pow(D, M));
			R = R.Normalize();
		}
		R = R * U;
		sum += R;
	}

	acceleration += sum;
}

void AIManager::avoid(Vector2D position, Vector2D targetPosition, Vector2D & acceleration, const float maxAccel)
{
	float disSq = Vector2D::DistanceSq(position, targetPosition);
	Vector2D x = (position - targetPosition).Normalize();
	acceleration += x * std::min(0.1f * disSq, maxAccel);
}


void AIManager::process()
{
	// FIND CLOSEST ABDUCTOR TO EACH ASTRONAUT
	for (Astronaut* astronaut : m_astronauts)
	{
		if (astronaut->isOnGround())
		{
			float closestDistance = std::numeric_limits<float>::max();
			Abductor* closestAbductor = nullptr;
			Vector2D closestAstronautPosition = NULL;
			int abductorIndex;
			
			for (int i = 0; i < m_abductors.size(); i++)
			{
				Abductor* a = m_abductors[i];

				if (!a->isAbducting())
				{
					float dist = Vector2D::DistanceSq(a->getPosition(), astronaut->getPosition());
					float dist2 = Vector2D::DistanceSq(a->getPosition(), (astronaut->getPosition() + Vector2D(m_levelBounds.width * 9, 0)));
					
					if (dist < closestDistance)
					{
						abductorIndex = i;
						closestDistance = dist;
						closestAbductor = a;
						closestAstronautPosition = astronaut->getPosition();
					}
					
					if (dist2 < closestDistance)
					{
						abductorIndex = i;
						closestDistance = dist2;
						closestAbductor = a;
						closestAstronautPosition = (astronaut->getPosition() + Vector2D(m_levelBounds.width * 9, 0));
					}
				}
			}

			if (closestAbductor != nullptr)
			{
				astronaut->setClosestAbductor(closestAbductor, m_abductors[abductorIndex]->getPosition());
				closestAbductor->setClosestAstronaut(closestAstronautPosition, astronaut);
			}
		}
	}
}


void AIManager::jumpToRandomPosition(Vector2D& position)
{
	float x = rand() % (int)m_levelBounds.width;
	float y = rand() % (int)m_levelBounds.height;
	position = Vector2D(m_levelBounds.left + x, m_levelBounds.top + y);
}