#include "stdafx.h"
#include "PowerUp.h"


PowerUp::PowerUp(int type, sf::Vector2f position, sf::Vector2f size) 
	: GameObject(sf::FloatRect(position, size)),
	  m_type(type),
	  m_timeToLive(10),
	  m_position(position)
{
	m_shape = sf::RectangleShape(size);
	m_shape.setPosition(position);
	m_bounds.left = m_position.x;
	m_bounds.top = m_position.y;
	initializeTexture();
}


PowerUp::~PowerUp()
{
}


void PowerUp::initializeTexture()
{
	switch (m_type)
	{
	case PowerUpTypes::HYPERJUMP:
		m_shape.setTexture(AssetLoader::getInstance()->findTextureByKey("hyperjump"));
		break;
	case PowerUpTypes::MORE_FIRE_RATE:
		m_shape.setTexture(AssetLoader::getInstance()->findTextureByKey("firerate"));
		break;
	case PowerUpTypes::INVINCIBILITY:
		m_shape.setTexture(AssetLoader::getInstance()->findTextureByKey("invincibility"));
		break;
	case PowerUpTypes::EMP:
		m_shape.setTexture(AssetLoader::getInstance()->findTextureByKey("emp"));
		break;
	}
}


void PowerUp::Update(float dt)
{
	m_timeToLive -= dt;

	if (m_timeToLive <= 0)
	{
		kill();
	}
}

void PowerUp::Draw(sf::RenderWindow & window)
{
	window.draw(m_shape);
}

void PowerUp::DrawWithXOffset(sf::RenderWindow & window, float xOffset)
{
	m_shape.move(sf::Vector2f(xOffset, 0));
	window.draw(m_shape);
	m_shape.move(sf::Vector2f(-xOffset, 0));
}

void PowerUp::wrapPositions(Camera & cam)
{
	cam.Wrap(m_position);
	m_shape.setPosition(m_position.toSFMLVector());
}

int PowerUp::GetType()
{
	return m_type;
}
