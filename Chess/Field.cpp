#include "Field.h"

Field::Field()
{
	_image.loadFromFile("../Chess/Images/chessboard.png");
	_texture.loadFromImage(_image);
	_sprite.setTexture(_texture);
}

Field::~Field()
{
}

void Field::processEvents()
{
	isClicked = sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

void Field::update(sf::Time deltaTime)
{

}

void Field::setScale(const sf::Vector2f &vec)
{
	_sprite.setScale(vec);
}

sf::Vector2u Field::getSizeOfTexture()
{
	return _texture.getSize();
}

void Field::setSpriteFromTexture(const sf::Texture &texture)
{
	_sprite.setTexture(texture);
}

void Field::setStartPosition(const sf::Vector2f &vec)
{
	_sprite.setPosition(vec);
}

void Field::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}


