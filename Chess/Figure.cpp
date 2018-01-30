#include "Figure.h"


//const sf::Vector2i &vec1, const sf::Vector2i &vec2
Figure::Figure(const std::string &name, const std::string &color)
{
	_name = name;
	_color = color;
	//std::cout << _name << "\t" << _color << std::endl;
	_image.loadFromFile("../Chess/Images/"+_name+".png");
	_texture.loadFromImage(_image);
	_sprite.setTexture(_texture);
	_sprite.setTextureRect(sf::IntRect(_color == "white" ? 0 : _image.getSize().x / 2, 0, _image.getSize().x / 2, _image.getSize().y));
	//_sprite.setTextureRect(sf::IntRect(vec1, vec2));
}

Figure::~Figure()
{
}

void Figure::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}
