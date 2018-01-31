#pragma once
#include "Element.h"

class Figure : public Element
{
public:
	Figure(const std::string & name, const std::string & color);
	~Figure();

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const override;
	virtual void processEvents(sf::Event &event) override;
	virtual void update() override;
	void updateCoordinates(sf::Vector2i &pos);

	bool isMove = false;
	std::string _name;
	std::string _color;
	
	friend class Field;

protected:

};

