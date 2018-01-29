#pragma once
#include "Field.h"
#include <string>
#include <iostream>

class Figure : public Field
{
public:
	Figure(const std::string & name, const std::string & color);
	~Figure();
	void setSprite(const sf::Vector2i &vec1, const sf::Vector2i &vec2);

	std::string _name;
	std::string _color;
	
private:

};

