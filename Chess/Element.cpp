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

void Element::setStartPosition(const sf::Vector2f & vec)
{
	_sprite.setPosition(vec);
}
//
//void Element::draw(sf::RenderTarget & target, sf::RenderStates states) const
//{
//	target.draw(_sprite, states);
//}
