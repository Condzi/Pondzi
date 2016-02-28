#include <SFML\Graphics.hpp>
#include <iostream>
#include "Ball.h"

Ball::Ball(float ballRadious, sf::Vector2f vecPos)
{
	ballShape.setRadius(ballRadious);
	vectorPosition = vecPos;
}

void Ball::draw(sf::RenderWindow & window)
{
	window.draw(ballShape);
}

void Ball::update(float frameTime)
{
	ballShape.move(vectorPosition.x * frameTime, vectorPosition.y *frameTime);
}
