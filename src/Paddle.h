#pragma once

#include <SFML\Graphics.hpp>

class Paddle
{
	friend class Game;

	sf::RectangleShape paddleShape;
	sf::Vector2f vectorPosition;
	float multiplier;
	float maxY;

public:
	Paddle(sf::Vector2f paddleSize = sf::Vector2f(10,100), 
			sf::Vector2f startPos = sf::Vector2f(0,0), 
			sf::Vector2f vectorPos = sf::Vector2f(0,0),
					float multi = 25,
					float borderY = 500.0);

	void update(float frameTime);
	void draw(sf::RenderWindow &window);

	void checkEvent(sf::Keyboard::Key upKey = sf::Keyboard::Key::Up, 
					sf::Keyboard::Key downKey = sf::Keyboard::Key::Down,
					float speed = 0.5);
};