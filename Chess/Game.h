#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Field.h"
#include "Figure.h"

class Game
{
public:
	Game(const Game &) = delete;
	Game & operator=(const Game &) = delete;
	Game();
	~Game();

	void run(int minimumFramePerSeconds = 60);

private:
	void processEvents();
	void update(sf::Time deltaTime);
	void render();

	sf::RenderWindow _window;
	Field _field;
	std::vector<Figure*> _figures;
};

