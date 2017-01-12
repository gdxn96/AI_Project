#include "stdafx.h"
#include "Player.h"
#include "InputManager.h"


Player::Player(sf::Vector2f position, sf::Vector2f size, Vector2D acceleration, Vector2D maxSpeed)
	: GameObject(sf::FloatRect(position, size), true),
	  ACCELERATION(acceleration),
	  MAX_SPEED(maxSpeed),
	  m_position(position),
	  m_shape(size),
	  m_facingDirection(1, 0),
	  m_bulletsPerSecond(10),
	  m_shooting(false)
{
	m_shape.setPosition(m_position.toSFMLVector());
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
}


void Player::Update(float dt)
{
	UpdateSpeed(dt);
	UpdateDirection();

	if (m_shooting)
	{
		UpdateShootState(dt);
	}

	AIManager::move(dt, m_position, m_speed * m_direction);
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
		m_targetDirection.x = Vector2D::LEFT.x;
		m_facingDirection.x = -1;
		break;
	case EventListener::KeyDownEvent::DOWN:
		m_targetDirection.y = Vector2D::DOWN.y;
		break;
	case EventListener::KeyDownEvent::RIGHT:
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
		AIManager::accelerate(dt, m_speed, accel, targSpeed);
	}
	else if (m_targetDirection.x == 0 && m_direction.x != 0)
	{
		Vector2D accel = Vector2D(-ACCELERATION.x, 0);
		Vector2D targSpeed = Vector2D(0, 0);
		AIManager::accelerate(dt, m_speed, accel, targSpeed);
	}

	if (m_targetDirection.y != 0)
	{
		m_speed.y = MAX_SPEED.y;
	}
	else if (m_direction.y != 0)
	{
		Vector2D accel = Vector2D(0, -ACCELERATION.y);
		Vector2D targSpeed = Vector2D(0, 0);
		AIManager::accelerate(dt, m_speed, accel, targSpeed);
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