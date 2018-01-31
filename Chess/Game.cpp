#include "Game.h"


Game::Game() : _window(sf::VideoMode(WIDTH, HEIGHT),"Game")
{
	class
	{
	public:
		char *board2[8][8] =
		{
		{ "castle", "knight", "bishop", "queen", "king", "bishop", "knight", "castle" },
		{ "pawn" , "pawn" , "pawn" , "pawn" , "pawn" , "pawn" , "pawn" , "pawn" },
		{ "empty", "empty", "empty", "empty", "empty", "empty", "empty", "empty" },
		{ "empty", "empty", "empty", "empty", "empty", "empty", "empty", "empty" },
		{ "empty", "empty", "empty", "empty", "empty", "empty", "empty", "empty" },
		{ "empty", "empty", "empty", "empty", "empty", "empty", "empty", "empty" },
		{ "pawn" , "pawn" , "pawn" , "pawn" , "pawn" , "pawn" , "pawn" , "pawn" },
		{ "castle", "knight", "bishop", "king", "queen", "bishop", "knight", "castle" },
		};
		void operator()(sf::Vector2i &pos, std::string &name)
		{
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					if (board2[i][j] == "empty") continue;
					if (board2[i][j] == name)
					{
						pos.x = j;
						pos.y = i;
						//std::cout << "\ti = " << i << "\tj = " << j << "\tboard2[i][j] = " << board2[i][j] << "\tpos.x = " << pos.x << "\tpos.y = " << pos.y << std::endl;
						board2[i][j] = "zero";
						goto breakLoop;
					}
				}
			}
		breakLoop:
			return;
		}
		void setFigure(std::vector<Figure*> &_figures, std::string &name, std::string &color, sf::Vector2i &pos, int &k)
		{
			_figures.push_back(new Figure(name, color));
			(*this)(pos, name);
			std::cout << pos.x << "\t" << pos.y << "\t" << color << "\t" << name << std::endl;
			if (k == 9 || k == 10) this->show();
			_figures[k]->setPosition(sf::Vector2f(800 / 8 * pos.x, 800 / 8 * pos.y));
			k++;
		}
		void show()
		{
			std::cout << std::endl;
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					std::cout << board2[i][j] << "\t";
				}
				std::cout<<std::endl;
			}
		}
	} getStartCoord;

	int k = 0;
	sf::Vector2i pos;
	//enum figuresNameEnum { pawn = 6, castle = 1, knight = 2, bishop = 3, queen = 4, king = 5};
	std::vector<std::string> figuresName = { "pawn", "castle", "knight", "bishop", "queen", "king" };
	std::vector<std::string> figuresColor = { "white", "black" };
	for (auto it1 = figuresColor.begin(); it1 != figuresColor.end(); it1++)
	{
		for (auto it2 = figuresName.begin(); it2 != figuresName.end(); it2++)
		{
			if (*it2 == "pawn")
				for (int l = 0; l < 8; l++)	getStartCoord.setFigure(_figures, *it2, *it1, pos, k);
			else if (*it2 == "king") getStartCoord.setFigure(_figures, *it2, *it1, pos, k);
			else if (*it2 == "queen") getStartCoord.setFigure(_figures, *it2, *it1, pos, k);
			else if (*it2 == "castle" || *it2 == "knight" || *it2 == "bishop")
				for (int l = 0; l < 2; l++)	getStartCoord.setFigure(_figures, *it2, *it1, pos, k);
		}
	}
	getStartCoord.show();	
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
	for (auto it = _figures.begin(); it != _figures.end(); it++)
	{
		(*it)->draw(_window);
	}
	_window.display();
}