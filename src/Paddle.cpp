#include <iostream>
#include "Paddle.h"

Paddle::Paddle(sf::Vector2f paddleSize, sf::Vector2f startPos, sf::Vector2f vectorPos, float multi, float borderY)
{
	paddleShape.setSize(paddleSize);
	paddleShape.setPosition(startPos);
	vectorPosition = vectorPos;
	multiplier = multi;
	maxY = borderY;
}

void Paddle::update(float frameTime)
{
	if (paddleShape.getPosition().y + paddleShape.getSize().y > maxY || paddleShape.getPosition().y < 0)
	{
		vectorPosition.x = 0;

		if (paddleShape.getPosition().y <= 0)
		{
			paddleShape.setPosition(sf::Vector2f(paddleShape.getPosition().x, 0));
		}
		
		else if (paddleShape.getPosition().y + paddleShape.getSize().y >= maxY)
		{
			paddleShape.setPosition(sf::Vector2f(paddleShape.getPosition().x, maxY - paddleShape.getSize().y));
		}
	}

	if (vectorPosition.y < 0)
	{	
		if (vectorPosition.y + multiplier / 10 > 0)
		{
			vectorPosition.y = 0;
		}
		else
		{
			vectorPosition.y += multiplier / 10;
		}
	}

	else if (vectorPosition.y > 0)
	{
		if (vectorPosition.y - multiplier / 10 < 0)
		{
			vectorPosition.y = 0;
		}
		else
		{
			vectorPosition.y -= multiplier / 10;
		}
	}

	paddleShape.move(vectorPosition.x * frameTime, vectorPosition.y * frameTime);
}

void Paddle::draw(sf::RenderWindow & window)
{
	window.draw(paddleShape);
}

void Paddle::checkEvent(sf::Keyboard::Key upKey, sf::Keyboard::Key downKey, float speed)
{
	if (sf::Keyboard::isKeyPressed(upKey) && paddleShape.getPosition().y - speed * multiplier > 0)
	{
		vectorPosition.y -= speed * multiplier;		
	}

	else if (sf::Keyboard::isKeyPressed(downKey) && paddleShape.getPosition().y + speed * multiplier + paddleShape.getSize().y < maxY)
	{
		vectorPosition.y += speed * multiplier;
	}
}
