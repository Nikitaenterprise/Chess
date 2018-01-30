#pragma once
#include "Element.h"

class Figure : public Element
{
public:
	Figure(const std::string & name, const std::string & color);
	~Figure();
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const override;

	std::string _name;
	std::string _color;
	
protected:

};

