#include "stdafx.h"
#include "AIManager.h"
#include <limits.h>



Player* AIManager::m_player = nullptr;
vector<Astronaut*> AIManager::m_astronauts;
std::vector<Boid*> AIManager::m_swarmObjects;
std::vector<Boid*> AIManager::m_flockObjects;
std::vector<Abductor*> AIManager::m_abductors;



void AIManager::registerPlayer(Player* player)
{
	m_player = player;
}

void AIManager::registerAstronaut(Astronaut* astronaut)
{
	m_astronauts.push_back(astronaut);
}

void AIManager::registerSwarmBoid(Boid * b)
{
	m_swarmObjects.push_back(b);
}

void AIManager::registerFlockBoid(Boid * b)
{
	m_flockObjects.push_back(b);
	Abductor * a = dynamic_cast<Abductor*>(b);
	if (a != nullptr)
	{
		m_abductors.push_back(a);
	}
}

void AIManager::unregisterBoid(Boid * b)
{
	std::remove(m_flockObjects.begin(), m_flockObjects.end(), b);
	std::remove(m_abductors.begin(), m_abductors.end(), b);
	std::remove(m_swarmObjects.begin(), m_swarmObjects.end(), b);
}



void AIManager::unregisterPlayer()
{
	m_player = nullptr;
}

void AIManager::unregisterAstronaut(Astronaut* astronaut)
{
	std::remove(m_astronauts.begin(), m_astronauts.end(), astronaut);
}



Vector2D AIManager::getPlayerPos()
{
	return m_player->getPosition();
}

Vector2D AIManager::getClosestAstronautPos(Vector2D position)
{
	int index = 0;
	float closestDistance = std::numeric_limits<float>::max();
	
	for (int i = 0; i < m_astronauts.size(); i++)
	{
		Vector2D astronautPosition = m_astronauts[i]->getPosition();
		float newDistance = Vector2D::Distance(position, astronautPosition);

		if (newDistance < closestDistance)
		{
			index = i;
			closestDistance = newDistance;
		}
	}

	if (index < m_astronauts.size())
	{
		return m_astronauts[index]->getPosition();
	}
	else
	{
		return NULL;
	}
}



void AIManager::wander(float dt, float& timeRemaining, int maxTime, Vector2D& direction, bool horizontalOnly)
{
	timeRemaining -= dt;

	if (timeRemaining <= 0)
	{
		timeRemaining = rand() % (maxTime + 1);
		direction.x = rand() & 1 ? 1 : -1;
		direction.y = horizontalOnly ? 0 : (rand() & 1 ? 1 : -1);
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

void AIManager::swarm(Boid * b, Vector2D& position, Vector2D& acceleration)
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

	float A = 0.1;
	float B = 0.8;
	float N = 0.4;
	float M = 0.8;
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

void AIManager::process()
{
	for (Astronaut* astronaut : m_astronauts)
	{
		std::sort(m_abductors.begin(), m_abductors.end(),
			[&](Abductor* a, Abductor* b) {return Vector2D::DistanceSq(a->getPosition(), astronaut->getPosition()) > Vector2D::DistanceSq(b->getPosition(), astronaut->getPosition()); });
		m_abductors.front()->setTargetAstronaut(astronaut);
	}
}

