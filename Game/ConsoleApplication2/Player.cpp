#include "stdafx.h"
#include "Player.h"
#include "InputManager.h"


Player::Player(sf::Vector2f position, sf::Vector2f size, Vector2D acceleration, Vector2D maxSpeed)
	: HealthObject(50000, sf::FloatRect(position, size), true),
	  ACCELERATION(acceleration),
	  MAX_SPEED(maxSpeed),
	  m_position(position),
	  m_shape(size),
	  m_facingDirection(1, 0),
	  NORMAL_FIRERATE(5),
	  m_bulletsPerSecond(5),
	  MAX_FIRERATE(10),
	  m_shooting(false),
	  m_canHyperjump(false),
	  m_canUseSmartBomb(true),
	  BOMB_COOLDOWN(60),
	  MAX_TIME_INCREASED_FIRE_RATE(5),
	  m_timeTillIncreasedFireRateEnds(0),
	  MAX_INVINCIBILITY_TIME(5),
	  m_timeTillInvincibilityEnds(0),
	  m_canUseEMP(false)
{
	m_shape.setPosition(m_position.toSFMLVector());
	m_shape.setTexture(AssetLoader::getInstance()->findTextureByKey("player"));
	InitializeEvents();
}


Player::~Player()
{
}


void Player::InitializeEvents()
{
	InputManager* input = InputManager::getInstance();
	input->AddListener(static_cast<int>(EventListener::KeyDownEvent::UP), this);
	input->AddListener(static_cast<int>(EventListener::KeyDownEvent::LEFT), this);
	input->AddListener(static_cast<int>(EventListener::KeyDownEvent::DOWN), this);
	input->AddListener(static_cast<int>(EventListener::KeyDownEvent::RIGHT), this);
	input->AddListener(static_cast<int>(EventListener::KeyUpEvent::UP), this);
	input->AddListener(static_cast<int>(EventListener::KeyUpEvent::LEFT), this);
	input->AddListener(static_cast<int>(EventListener::KeyUpEvent::DOWN), this);
	input->AddListener(static_cast<int>(EventListener::KeyUpEvent::RIGHT), this);
	input->AddListener(static_cast<int>(EventListener::GenericEvent::SHOOT), this);
	input->AddListener(static_cast<int>(EventListener::GenericEvent::NO_SHOOT), this);
	input->AddListener(static_cast<int>(EventListener::GenericEvent::HYPERJUMP), this);
	input->AddListener(static_cast<int>(EventListener::GenericEvent::SMART_BOMB), this);
	input->AddListener(static_cast<int>(EventListener::GenericEvent::EMP), this);
}


void Player::Update(float dt)
{
	UpdateSpeed(dt);
	UpdateDirection();
	UpdateSmartBomb(dt);
	UpdateIncreasedFireRate(dt);
	UpdateInvincibility(dt);

	if (m_shooting)
	{
		UpdateShootState(dt);
	}

	PhysicsManager::move(dt, m_position, m_speed * m_direction);
	PhysicsManager::BindPositionToLevel(m_position);
	m_shape.setPosition(m_position.toSFMLVector());
	m_bounds.left = m_position.x;
	m_bounds.top = m_position.y;
}


void Player::Draw(sf::RenderWindow& window)
{
	window.draw(m_shape);
}

void Player::DrawWithXOffset(sf::RenderWindow & window, float xOffset)
{
	m_shape.move(sf::Vector2f(xOffset, 0));
	window.draw(m_shape);
	m_shape.move(sf::Vector2f(-xOffset, 0));
}

void Player::onGenericEvent(GenericEvent evt)
{
	switch (evt)
	{
	case EventListener::GenericEvent::SHOOT:
		m_shooting = true;
		break;
	case EventListener::GenericEvent::NO_SHOOT:
		m_shooting = false;
		break;
	case EventListener::GenericEvent::HYPERJUMP:
		if (m_canHyperjump)
		{
			m_canHyperjump = false;
			AIManager::jumpToRandomPosition(m_position);
		}
		break;
	case EventListener::GenericEvent::SMART_BOMB:
		if (m_canUseSmartBomb)
		{
			std::vector<GameObject*> objectsOnScreen = CollisionManager::GetObjectsOnScreen();
			m_canUseSmartBomb = false;
			m_timeTillBombActive = BOMB_COOLDOWN;

			for (GameObject* object : objectsOnScreen)
			{
				object->kill();
			}
		}
		break;
	case EventListener::GenericEvent::EMP:
		if (m_canUseEMP)
		{
			std::vector<GameObject*> enemiesOnScreen = CollisionManager::GetEnemiesOnScreen();
			m_canUseEMP = false;

			for (GameObject* enemy : enemiesOnScreen)
			{
				Abductor* abductor = dynamic_cast<Abductor*>(enemy);
				Mutant* mutant = dynamic_cast<Mutant*>(enemy);
				Nest* nest = dynamic_cast<Nest*>(enemy);

				if (abductor != NULL)
				{
					abductor->destroyElectrics();
				}

				if (mutant != NULL)
				{
					mutant->destroyElectrics();
				}

				if (nest != NULL)
				{
					nest->destroyElectrics();
				}
			}
		}
		break;
	}
}

void Player::onKeyDown(KeyDownEvent evt)
{
	switch (evt)
	{
	case EventListener::KeyDownEvent::UP:
		m_targetDirection.y = Vector2D::UP.y;
		break;
	case EventListener::KeyDownEvent::LEFT:
		if (m_targetDirection.x == Vector2D::RIGHT.x || m_targetDirection.x == 0 && m_direction.x == 1)
		{
			m_speed = 0;
		}
		m_targetDirection.x = Vector2D::LEFT.x;
		m_facingDirection.x = -1;
		break;
	case EventListener::KeyDownEvent::DOWN:
		m_targetDirection.y = Vector2D::DOWN.y;
		break;
	case EventListener::KeyDownEvent::RIGHT:
		if (m_targetDirection.x == Vector2D::LEFT.x || m_targetDirection.x == 0 && m_direction.x == -1)
		{
			m_speed = 0;
		}
		m_targetDirection.x = Vector2D::RIGHT.x;
		m_facingDirection.x = 1;
		break;
	}
}

void Player::onKeyUp(KeyUpEvent evt)
{
	switch (evt)
	{
	case EventListener::KeyUpEvent::UP:
		m_targetDirection.y = m_targetDirection.y == Vector2D::UP.y ? 0 : m_targetDirection.y;
		break;
	case EventListener::KeyUpEvent::LEFT:
		m_targetDirection.x = m_targetDirection.x == Vector2D::LEFT.x ? 0 : m_targetDirection.x;
		break;
	case EventListener::KeyUpEvent::DOWN:
		m_targetDirection.y = m_targetDirection.y == Vector2D::DOWN.y ? 0 : m_targetDirection.y;
		break;
	case EventListener::KeyUpEvent::RIGHT:
		m_targetDirection.x = m_targetDirection.x == Vector2D::RIGHT.x ? 0 : m_targetDirection.x;
		break;
	}
}


void Player::wrapPositions(Camera & cam)
{
	cam.Wrap(m_position);
	m_shape.setPosition(m_position.toSFMLVector());

	cam.SetCenter(m_position.toSFMLVector());
}



void Player::UpdateSpeed(float dt)
{
	if (m_targetDirection.x != 0)
	{
		Vector2D accel = Vector2D(ACCELERATION.x, 0);
		Vector2D targSpeed = Vector2D(MAX_SPEED.x, 0);
		PhysicsManager::accelerate(dt, m_speed, accel, targSpeed);
	}
	else if (m_targetDirection.x == 0 && m_direction.x != 0)
	{
		Vector2D accel = Vector2D(-ACCELERATION.x, 0);
		Vector2D targSpeed = Vector2D(0, 0);
		PhysicsManager::accelerate(dt, m_speed, accel, targSpeed);
	}

	if (m_targetDirection.y != 0)
	{
		m_speed.y = MAX_SPEED.y;
	}
	else if (m_direction.y != 0)
	{
		Vector2D accel = Vector2D(0, -ACCELERATION.y);
		Vector2D targSpeed = Vector2D(0, 0);
		PhysicsManager::accelerate(dt, m_speed, accel, targSpeed);
	}
}

void Player::UpdateSmartBomb(float dt)
{
	if (!m_canUseSmartBomb)
	{
		m_timeTillBombActive -= dt;

		if (m_timeTillBombActive <= 0)
		{
			m_canUseSmartBomb = true;
		}
	}
}

void Player::UpdateIncreasedFireRate(float dt)
{
	if (m_timeTillIncreasedFireRateEnds > 0)
	{
		m_timeTillIncreasedFireRateEnds -= dt;

		if (m_timeTillIncreasedFireRateEnds <= 0)
		{
			m_bulletsPerSecond = NORMAL_FIRERATE;
		}
	}
}

void Player::UpdateInvincibility(float dt)
{
	if (isInvincible())
	{
		m_timeTillInvincibilityEnds -= dt;
	}
}



void Player::UpdateDirection()
{
	if (m_speed.x == 0)
	{
		m_direction.x = 0;
	}
	else if (m_targetDirection.x != 0)
	{
		m_direction.x = m_targetDirection.x;
	}

	if (m_speed.y == 0)
	{
		m_direction.y = 0;
	}
	else if (m_targetDirection.y != 0)
	{
		m_direction.y = m_targetDirection.y;
	}
}



void Player::UpdateShootState(float dt)
{
	m_timeTillNextShot -= dt;

	if (m_timeTillNextShot <= 0)
	{
		m_timeTillNextShot = 1.0f / m_bulletsPerSecond;
		EntityFactory::CreateBullet(Rect(m_bounds).getCentreCopy(), m_facingDirection);
	}
}


Vector2D Player::getPosition()
{
	return m_position;
}

void Player::addHyperJumpPowerUp()
{
	m_canHyperjump = true;
}

void Player::increaseFireRate()
{
	m_timeTillIncreasedFireRateEnds = MAX_TIME_INCREASED_FIRE_RATE;
	m_bulletsPerSecond = MAX_FIRERATE;
}

void Player::makeInvincible()
{
	m_timeTillInvincibilityEnds = MAX_INVINCIBILITY_TIME;
}

bool Player::isInvincible()
{
	return m_timeTillInvincibilityEnds > 0;
}

void Player::addEMP()
{
	m_canUseEMP = true;
}