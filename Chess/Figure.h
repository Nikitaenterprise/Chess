#pragma once
#include "Element.h"

class Figure : public Element
{
public:
	Figure(const std::string & name, const std::string & color);

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const override;
	virtual void processEvents(sf::Event &event, const sf::Window &window) override;
	virtual void update() override;
	void move(int i, int j);
	void changeColor(Figure *that, const sf::Color &color);
	bool canMoveHere(int i, int j);
	bool checkLine(int i, int j, int iOld, int jOld, int line);

	Figure *figurePtr = this;
	bool isMove = false;
	bool isFirsTimeMoving = true;
	std::string _name;
	std::string _color;
};

