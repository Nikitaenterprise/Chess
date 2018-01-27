#include "Figure.h"



Figure::Figure()
{
	_image.loadFromFile("../Chess/Images/chessboard.png");
	_texture.loadFromImage(_image);
	_sprite.setTexture(_texture);
}


Figure::~Figure()
{
}
