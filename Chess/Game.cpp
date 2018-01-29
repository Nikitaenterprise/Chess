#include "Game.h"


Game::Game() : _window(sf::VideoMode(WIDTH, HEIGHT),"Game")
{
	_field.setScale(sf::Vector2f(1.0f / (float(_field.getSizeOfTexture().x) / float(_window.getSize().x)), 
								1.0f / (float(_field.getSizeOfTexture().y) / float(_window.getSize().y))));
	_field.setStartPosition(sf::Vector2f(0, 0));

	std::vector<std::string> figuresName = { "pawn", "castle", "knight", "bishop", "queen", "king" };
	std::vector<std::string> figuresColor = { "white", "black" };
	for (auto it1 = figuresColor.begin(); it1 != figuresColor.end(); it1++)
	{
		for (auto it2 = figuresName.begin(); it2 != figuresName.end(); it2++)
		{
			if (*it2 == "pawn")
			{
				for (int j = 0; j < 8; j++)	_figures.push_back(new Figure((*it2), (*it1)));
			}
			else if (*it2 == "king" || *it2 == "queen")
			{
				_figures.push_back(new Figure((*it2), (*it1)));
			}
			else
			{
				for (int j = 0; j < 2; j++)	_figures.push_back(new Figure((*it2), (*it1)));
			}
		}
	}
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
	//_window.draw(_field);
	_field.draw(_window);
	_window.display();
}