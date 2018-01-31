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
	_sprite.setScale(float(0.2), float(0.2));
	//_sprite.setTextureRect(sf::IntRect(vec1, vec2));
}

Figure::~Figure()
{
}

void Figure::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}

void Figure::processEvents(sf::Event &event)
{
	//sf::Event event;
	if (event.type == 
		sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Left)
	{
		isMove = true;
		pos = static_cast<sf::Vector2f> (sf::Mouse::getPosition());
		std::cout << pos.x << "\t" << pos.y << std::endl;
	}
	else if (event.type ==
		sf::Event::MouseButtonReleased && 
		event.mouseButton.button == sf::Mouse::Left)
		isMove = false;
}

void Figure::update()
{
	if (isMove)
	{
		pos.x += dPos.x;
		pos.y += dPos.y;
	}
}

void Figure::updateCoordinates(sf::Vector2i &pos)
{
	
}
