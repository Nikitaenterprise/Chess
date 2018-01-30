#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>

class Element : protected sf::Drawable
{
public:
	Element(const Element &) = delete;
	Element & operator=(const Element &) = delete;
	Element();
	~Element();

	void setScale(const sf::Vector2f &vec);
	sf::Vector2u getSizeOfTexture();
	void setSpriteFromTexture(const sf::Texture &texture);
	void setStartPosition(const sf::Vector2f &vec);
	//virtual void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const override;

protected:
	sf::Image _image;
	sf::Texture _texture;
	sf::Sprite _sprite;
};

