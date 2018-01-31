#include "Game.h"


Game::Game() : _window(sf::VideoMode(WIDTH, HEIGHT),"Game")
{
	class
	{
	public:
		void operator()(sf::Vector2i &pos, int id)
		{
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					int n = board[i][j];
					if (n == 0) continue;
					if (n == id)
					{
						pos.y = abs(n);
						pos.x = n > 0 ? 1 : 0;
						std::cout << "id = " << id  << "\ti = " << i << "\tj = " << j << "\tn = " << n << "\tpos.x = " << pos.x << "\tpos.y = " << pos.y << std::endl;
						board[i][j] = 9;
						break;
					}
				}
			}
		}
		int board[8][8] = {
								-1,-2,-3,-4,-5,-3,-2,-1,
								-6,-6,-6,-6,-6,-6,-6,-6,
								0, 0, 0, 0, 0, 0, 0, 0,
								0, 0, 0, 0, 0, 0, 0, 0,
								0, 0, 0, 0, 0, 0, 0, 0,
								0, 0, 0, 0, 0, 0, 0, 0,
								6, 6, 6, 6, 6, 6, 6, 6,
								1, 2, 3, 4, 5, 3, 2, 1 
														};
		char *board2[8][8] =
		{
		{ "castle", "knight", "bishop", "queen", "king", "bishop", "knight", "castle" },
		{ "pawn" , "pawn" , "pawn" , "pawn" , "pawn" , "pawn" , "pawn" , "pawn" },
		{ "empty", "empty", "empty", "empty", "empty", "empty", "empty", "empty" },
		{ "empty", "empty", "empty", "empty", "empty", "empty", "empty", "empty" },
		{ "empty", "empty", "empty", "empty", "empty", "empty", "empty", "empty" },
		{ "empty", "empty", "empty", "empty", "empty", "empty", "empty", "empty" },
		{ "pawn" , "pawn" , "pawn" , "pawn" , "pawn" , "pawn" , "pawn" , "pawn" },
		{ "castle", "knight", "bishop", "queen", "king", "bishop", "knight", "castle" },
		};
		void operator()(sf::Vector2i &pos, std::vector<std::string> *name)
		{
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					std::cout << board2[i][j] << "\t";
				}
			}
		}
		void show()
		{
			std::cout << std::endl;
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					std::cout << board[i][j] << "\t";
				}
				std::cout<<std::endl;
			}
		}
	} getStartCoord;

	int k = 0;
	sf::Vector2i pos;
	enum figuresNameEnum { pawn = 6, castle = 1, knight = 2, bishop = 3, queen = 4, king = 5};
	std::vector<std::string> figuresName = { "pawn", "castle", "knight", "bishop", "queen", "king" };
	std::vector<std::string> figuresColor = { "white", "black" };
	for (auto it1 = figuresColor.begin(); it1 != figuresColor.end(); it1++)
	{
		for (auto it2 = figuresName.begin(); it2 != figuresName.end(); it2++)
		{
			if (*it2 == "pawn")
			{
				for (int l = 0; l < 8; l++)
				{
					_figures.push_back(new Figure((*it2), (*it1)));
					getStartCoord(pos, figuresNameEnum(pawn));
					_figures[k]->setPosition(sf::Vector2f(l * 800 / 8 * pos.x, 800 / 8 * pos.y));
					k++;
					//getStartCoord(pos, );
				}
			}
			else if (*it2 == "king")
			{
				_figures.push_back(new Figure((*it2), (*it1)));
				getStartCoord(pos, figuresNameEnum(king));
				_figures[k]->setPosition(sf::Vector2f(800 / 8 * pos.y, 800 / 8 * pos.x));
				k++;
			}
			else if (*it2 == "queen")
			{
				_figures.push_back(new Figure((*it2), (*it1)));
				getStartCoord(pos, figuresNameEnum(queen));
				_figures[k]->setPosition(sf::Vector2f(800 / 8 * pos.y, 800 / 8 * pos.x));
				k++;
			}
			else
			{
				for (int l = 0; l < 2; l++)	_figures.push_back(new Figure((*it2), (*it1)));
				getStartCoord(pos, figuresNameEnum(knight));
				_figures[k]->setPosition(sf::Vector2f(800 / 8 * pos.y, 800 / 8 * pos.x));
				k++;
			}
		}
	}
	getStartCoord.show();
	//for (int i = 0; i < 8; i++)
	//{
	//	for (int j = 0; j < 8; j++)
	//	{
	//		int n = board[i][j];
	//		if (n == 0) continue;
	//		int x = abs(n) - 1;
	//		int y = n > 0 ? 1 : 0;
	//		std::cout << x << "\t" << y << "\t" << n << std::endl;
	//		/*for (auto it = _figures.begin(); it != _figures.end(); it++)
	//		{
	//			(*it)->setPosition(sf::Vector2f(800/8*i, 800/8*j));
	//		}*/
	//		_figures[k]->setPosition(sf::Vector2f(800 / 8 * j, 800 / 8 * i));
	//		k++;
	//	}
	//}
	
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