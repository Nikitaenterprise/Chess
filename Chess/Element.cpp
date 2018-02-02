#include "Element.h"

Element::Element()
{
}

Element::~Element()
{
}

void Element::setScale(const sf::Vector2f & vec)
{
	_sprite.setScale(vec);
}

sf::Vector2u Element::getSizeOfTexture()
{
	return _texture.getSize();
}

void Element::setSpriteFromTexture(const sf::Texture & texture)
{
	_sprite.setTexture(texture);
}

void Element::setPosition(const sf::Vector2f & vec)
{
	sf::Vector2f offset(52, 52);
	sf::Vector2f temp(_image.getSize().x / 4 - offset.x, _image.getSize().y / 2 - offset.y);
	_sprite.setPosition(vec);
	this->pos = vec+temp;
	_oldPos = this->_sprite.getPosition();
}

void Element::setGamePtr(Game * game)
{
	_thisGame = game;
}
