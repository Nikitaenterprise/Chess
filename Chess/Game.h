#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
//#include "Element.h"


#define HEIGHT 800
#define WIDTH 800
class Field;
class Figure;
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
	std::vector<Field*> _field;
	std::vector<Figure*> _figures;
};

class Element : public sf::Drawable
{
public:
	
	Element(const Element &) = delete;
	Element & operator=(const Element &) = delete;
	Element();
	~Element();

	void setScale(const sf::Vector2f &vec);
	sf::Vector2u getSizeOfTexture();
	void setSpriteFromTexture(const sf::Texture &texture);
	void setPosition(const sf::Vector2f &vec);
	void setGamePtr(Game *game);
	virtual void processEvents(sf::Event &event, const sf::Window &window) = 0;
	virtual void update() = 0;

	sf::Vector2f pos;
	sf::Vector2f dPos;
	sf::Vector2f _oldPos;
	sf::Vector2f _newPos;

	Game *_thisGame;

protected:
	sf::Image _image;
	sf::Texture _texture;
	sf::Sprite _sprite;
};

#include "Field.h"
#include "Figure.h"