#pragma once
#include "Element.h"

class Field : public Element
{
public:
	Field(const Field &) = delete;
	Field & operator=(const Field &) = delete;
	Field();
	~Field();

	void processEvents();
	void update(sf::Time deltaTime);
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const override;
	bool isClicked;

protected:
	std::vector<sf::RectangleShape*> _fieldElement;
};

