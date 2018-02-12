#include "Game.h"
#include "Element.h"

Game::Game() : _window(sf::VideoMode(WIDTH, HEIGHT),"Game")
{
	class
	{
	public:
		char *startPosition[8][8] =
		{
		{ "wcastle", "wknight", "wbishop", "wqueen", "wking", "wbishop", "wknight", "wcastle" },
		{ "wpawn" , "wpawn" , "wpawn" , "wpawn" , "wpawn" , "wpawn" , "wpawn" , "wpawn" },
		{ "empty", "empty", "empty", "empty", "empty", "empty", "empty", "empty" },
		{ "empty", "empty", "empty", "empty", "empty", "empty", "empty", "empty" },
		{ "empty", "empty", "empty", "empty", "empty", "empty", "empty", "empty" },
		{ "empty", "empty", "empty", "empty", "empty", "empty", "empty", "empty" },
		{ "bpawn" , "bpawn" , "bpawn" , "bpawn" , "bpawn" , "bpawn" , "bpawn" , "bpawn" },
		{ "bcastle", "bknight", "bbishop", "bqueen", "bking", "bbishop", "bknight", "bcastle" },
		};
		void operator()(sf::Vector2i &pos, std::string &name)
		{
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					if (startPosition[i][j] == "empty") continue;
					if (startPosition[i][j] == name)
					{
						pos.x = j;
						pos.y = i;
						startPosition[i][j] = "empty";
						goto breakLoop;
					}
				}
			}
		breakLoop:
			return;
		};

		void setFigure(std::vector<Figure*> &_figures, std::string &name, std::string &color, sf::Vector2i &pos, int &k)
		{
			_figures.push_back(new Figure(name, color));
			(*this)(pos, color+name);
			_figures[k]->setPosition(sf::Vector2f(float(800 / 8 * pos.x), float(800 / 8 * pos.y)));
			k++;
		};
	} getStartCoord;

	int k = 0;
	sf::Vector2i pos;
	std::vector<std::string> figuresName = { "pawn", "castle", "knight", "bishop", "queen", "king" };
	std::vector<std::string> figuresColor = { "w", "b" };
	for (auto &color : figuresColor)
	{
		for (auto &name : figuresName)
		{
			if(name == "pawn")
				for (int l = 0; l < 8; l++)	getStartCoord.setFigure(_figures, name, color, pos, k);
			else if (name == "king" || name == "queen") getStartCoord.setFigure(_figures, name, color, pos, k);
			else if (name == "castle" || name == "knight" || name == "bishop")
				for (int l = 0; l < 2; l++)	getStartCoord.setFigure(_figures, name, color, pos, k);
		}
	}
	for (auto &obj : _figures) obj->setGamePtr(this);
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

Figure & Game::getBoardFigure(int i, int j)
{
	for (const auto &obj : _figures)
	{
		if (static_cast<int>(obj->_oldPos.x / 100) == i && static_cast<int>(obj->_oldPos.y / 100) == j)
			return *obj;
	}
}

void Game::deleteFigure(Figure  *figure)
{
	_figures.erase(std::remove(_figures.begin(), _figures.end(), figure), _figures.end());
	figure->~Figure();
	/*for (auto it = _figures.begin(); it != _figures.end(); ++it)
	{
		if ((*it) == figure)
		{
			it = _figures.erase(it);
			std::cout << "deleted " << figure->figurePtr << std::endl;
			figure->~Figure();
			break;
		}
	}*/
}

void Game::printBoard()
{
	std::cout << std::endl;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			std::cout << _board[i][j] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Game::processEvents()
{
	sf::Event event;
	while (_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed  
			|| (event.type == sf::Event::KeyPressed  
				&& event.key.code == sf::Keyboard::Escape))	_window.close();

		_field.processEvents(event, _window);
		for(auto it = _figures.begin(); it != _figures.end(); ++it) (*it)->processEvents(event, _window);
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) system("cls");
	}
}

void Game::update(sf::Time deltaTime)
{
	_field.update(deltaTime);
	for (const auto obj : _figures)	obj->update();
}

void Game::render()
{
	_window.clear();
	_window.draw(_field);
	for (const auto obj : _figures)	obj->draw(_window);
	_window.display();
}