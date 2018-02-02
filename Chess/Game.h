#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Element.h"
#include "Field.h"
#include "Figure.h"

#define HEIGHT 800
#define WIDTH 800

class Game
{
public:
	Game(const Game &) = delete;
	Game & operator=(const Game &) = delete;
	Game();
	~Game();
	
	void run(int minimumFramePerSeconds = 60);
	char *getBoardElement(int i, int j) { return _board[i][j]; };
	void setBoardElement(int i, int j, char *str) { _board[i][j] = str; };
	
	Game *_thisGame = this;
	char *_board[8][8] =
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
	
private:
	void processEvents();
	void update(sf::Time deltaTime);
	void render();

	sf::RenderWindow _window;
	Field _field;
	std::vector<Figure*> _figures;
};

