#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>

class Element : public sf::Drawable
{
	friend class Game;
public:
	Element(const Element &) = delete;
	Element & operator=(const Element &) = delete;
	Element();
	~Element();

	void setScale(const sf::Vector2f &vec);
	sf::Vector2u getSizeOfTexture();
	void setSpriteFromTexture(const sf::Texture &texture);
	void setPosition(const sf::Vector2f &vec);
	void setGamePtr(Game *game) { _thisGame = game; };
	virtual void processEvents(sf::Event &event, const sf::Window &window) = 0;
	virtual void update() = 0;

	sf::Vector2f pos;
	sf::Vector2f dPos;
	sf::Vector2f _oldPos;
	sf::Vector2f _newPos;

	Game *_thisGame = nullptr;

protected:
	sf::Image _image;
	sf::Texture _texture;
	sf::Sprite _sprite;
};

