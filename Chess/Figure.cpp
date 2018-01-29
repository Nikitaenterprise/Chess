#include "Figure.h"



Figure::Figure(const std::string &name, const std::string &color)
{
	_name = name;
	_color = color;
	std::cout << _name << "\t" << _color << std::endl;
}

Figure::~Figure()
{
}

void Figure::setSprite(const sf::Vector2i &vec1, const sf::Vector2i &vec2)
{
	_image.loadFromFile("../Chess/Images/Chess_Sprite.png");
	_texture.loadFromImage(_image);
	_sprite.setTexture(_texture);
	_sprite.setTextureRect(sf::IntRect(vec1, vec2));
}
