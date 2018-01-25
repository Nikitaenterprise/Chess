#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Game
{
public:
	Game(const Game &) = delete;
	Game & operator=(const Game &) = delete;
	Game();
	~Game();

	void run(int framePerSeconds = 60);

private:
	void processEvents();
	void update(sf::Time deltaTime);
	void render();

	sf::RenderWindow _window;
	sf::CircleShape _player;
};

