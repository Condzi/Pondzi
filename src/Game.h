#pragma once

#include <SFML\Graphics.hpp>
#include "Ball.h"
#include "Paddle.h"

class Game
{
	sf::RenderWindow window;
	Paddle player1;
	Paddle player2;
	Ball ball;

	sf::Font arial;
	sf::Text pointsViewed;

	int points[2];

	void resetPositions();
	
	void events();
	void windowEvents(sf::Event &event);
	
	void checkCollisions();
	void update(float frameTime);
	void draw();

public:
	Game(sf::Vector2u windowSize = sf::Vector2u(800, 600),
		std::string title = "Pondzi",
		int frameLimit = 30,
		std::string fontPath = "Resources/arial.ttf");

	void init();
	void play();
};