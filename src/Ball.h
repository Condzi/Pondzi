#pragma once

#include <SFML\Graphics.hpp>

class Ball
{
	friend class Game;

	sf::CircleShape ballShape;
	sf::Vector2f vectorPosition;

public:
	Ball(float ballRadious = 25,
		sf::Vector2f vecPos = sf::Vector2f(15, 15));

	void update(float frameTime);
	void draw(sf::RenderWindow &window);
};