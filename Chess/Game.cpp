#include "Game.h"

Game::Game() : _window(sf::VideoMode(800,600),"Game"), _player(150)
{
	_player.setFillColor(sf::Color::Green);
	_player.setPosition(10, 20);
}


Game::~Game()
{
}


void Game::run(int framePerSeconds)
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(double(1) / framePerSeconds);
	std::cout << "timeSinceLastUpdate = " << timeSinceLastUpdate.asMilliseconds() << std::endl;
	std::cout << "timePerFrame = " << timePerFrame.asMilliseconds() << std::endl;
	while (_window.isOpen())
	{
		processEvents();
		bool repaint = false;

		timeSinceLastUpdate += clock.restart();
		
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			repaint = true;
			update(timePerFrame);
		}
		if (repaint) render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
		{
			_window.close();
		}
	}
}


void Game::update(sf::Time deltaTime)
{

}


void Game::render()
{
	_window.clear();
	_window.draw(_player);
	_window.display();
}