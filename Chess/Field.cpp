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


void Field::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}


