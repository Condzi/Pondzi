#include <iostream>
#include <string>
#include "Game.h"

void Game::init()
{
	player1.maxY = window.getSize().y;
	player2.maxY = window.getSize().y;
	ball.ballShape.setRadius(10);
	ball.ballShape.setPointCount(4);

	pointsViewed.setFont(arial);
	pointsViewed.setPosition(window.getSize().x / 2, 0);

	resetPositions();
}

void Game::play()
{
	sf::Clock clock;
	sf::Time frameTime;
	sf::Event event;

	while (window.isOpen())
	{
		if (frameTime.asSeconds() < 0.1)
		{
			update(frameTime.asSeconds());

			clock.restart();
		}

		while (window.pollEvent(event))
		{
			windowEvents(event);	
		}
		
		events();

		checkCollisions();

		window.clear();

		draw();

		window.display();

		frameTime = clock.getElapsedTime();
	}
}

void Game::resetPositions()
{
	player1.paddleShape.setPosition(sf::Vector2f(0, window.getSize().y / 2));
	player1.vectorPosition.y = 0;
	player2.paddleShape.setPosition(window.getSize().x - player2.paddleShape.getSize().x, window.getSize().y/2);
	player2.vectorPosition.y = 0;

	ball.ballShape.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	ball.vectorPosition = sf::Vector2f(250, 0);
}

void Game::events()
{
	player1.checkEvent(sf::Keyboard::W, sf::Keyboard::S);
	player2.checkEvent();
}

void Game::windowEvents(sf::Event &event)
{
	if (event.type == sf::Event::Closed)
	{
		std::cout << "Closing...\n";
		window.close();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
	{
		std::cout << "DEBUG-> RESETING POSITIONS\n";
		resetPositions();
	}
}

void Game::checkCollisions()
{
	//kolizja z paletkami
	if (ball.ballShape.getGlobalBounds().intersects(player1.paddleShape.getGlobalBounds()) ||
		ball.ballShape.getGlobalBounds().intersects(player2.paddleShape.getGlobalBounds()))
	{
		ball.vectorPosition.x = -ball.vectorPosition.x * 1.05;
		
		if (ball.ballShape.getGlobalBounds().intersects(player1.paddleShape.getGlobalBounds()))
		{
			ball.vectorPosition.y = !ball.vectorPosition.y + player1.vectorPosition.y / player1.multiplier * player1.paddleShape.getPosition().y / 15;
			
			if (ball.ballShape.getPosition().y > player1.paddleShape.getPosition().y + player1.paddleShape.getGlobalBounds().height / 2)
			{
				ball.vectorPosition.y += 15;
			}
			else
			{
				ball.vectorPosition.y -= 15;
			}
		}
		else
		{
			ball.vectorPosition.y = !ball.vectorPosition.y + player2.vectorPosition.y / player1.multiplier * player1.paddleShape.getPosition().y / 15;

			if (ball.ballShape.getPosition().y > player2.paddleShape.getPosition().y + player2.paddleShape.getGlobalBounds().height / 2)
			{
				ball.vectorPosition.y += 15;
			}
			else
			{
				ball.vectorPosition.y -= 15;
			}
		}
	}
	
	//kolizja z brzegami okna (gora i dol)
	else if (ball.ballShape.getPosition().y < 0 || 
		ball.ballShape.getPosition().y + ball.ballShape.getRadius() * 2 > window.getSize().y)
	{
		ball.vectorPosition.y = -ball.vectorPosition.y;
	}

	//jezeli pilka bedzie za paletkami
	else if (ball.ballShape.getPosition().x < player1.paddleShape.getPosition().x)
	{
		std::cout << "\nSCORE! Player 2 point!\n";
		points[1]++;
		resetPositions();
	}
	else if (ball.ballShape.getPosition().x > player2.paddleShape.getPosition().x)
	{
		std::cout << "\nSCORE! Player 1 point!\n";
		points[0]++;
		resetPositions();
	}
}

void Game::update(float frameTime)
{
	ball.update(frameTime);

	player1.update(frameTime);
	player2.update(frameTime);

//	std::cout << "PLAYER 1: " << points[0] << "\n";
//	std::cout << "PLAYER 2: " << points[1] << "\n";
//	std::cout << "Wektor Ball X: " << ball.vectorPosition.x << " | Ball Y: " << ball.vectorPosition.y << "\n";
//	std::cout << "Pozycja Ball X:" << ball.ballShape.getPosition().x << " | Ball Y: " << ball.ballShape.getPosition().y << "\n";
}

void Game::draw()
{
	std::string points_string;
	
	points_string = std::to_string(points[0]);
	points_string += " : ";
	points_string += std::to_string(points[1]);

	pointsViewed.setString(points_string);

	ball.draw(window);

	player1.draw(window);
	player2.draw(window);

	window.draw(pointsViewed);
	
}

Game::Game(sf::Vector2u windowSize, std::string title, int frameLimit, std::string fontPath)
{
	window.create(sf::VideoMode(windowSize.x, windowSize.y, 1U), title, sf::Style::Close);
	window.setFramerateLimit(frameLimit);

	points[0] = 0;
	points[1] = 0;

	if (!arial.loadFromFile(fontPath))
	{
		//blad moze kiedys tutaj 
	}
}
