#include "Game.h"


Game::Game() : _window(sf::VideoMode(800,800),"Game")
{
	_field.setScale(sf::Vector2f(1.0f / (float(_field.getSizeOfTexture().x) / float(_window.getSize().x)), 
								1.0f / (float(_field.getSizeOfTexture().y) / float(_window.getSize().y))));
	_field.setStartPosition(sf::Vector2f(0, 0));

	
}

Game::~Game()
{
}

void Game::run(int minimumFramePerSeconds)
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate;
	sf::Time timePerFrame = sf::seconds(float(1) / minimumFramePerSeconds);
	while (_window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate = clock.restart();
		
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			update(timePerFrame);
		}
		update(timeSinceLastUpdate);
		render();
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
		_field.processEvents();
	}
}

void Game::update(sf::Time deltaTime)
{
	_field.update(deltaTime);
}

void Game::render()
{
	_window.clear();
	_window.draw(_field);
	_window.display();
}