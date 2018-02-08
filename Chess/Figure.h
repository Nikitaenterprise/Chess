#pragma once
#include "Element.h"

class Figure : public Element
{
public:
	Figure(const std::string & name, const std::string & color);
	~Figure();

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const override;
	virtual void processEvents(sf::Event &event, const sf::Window &window) override;
	virtual void update() override;
	void updateCoordinates(sf::Vector2i &pos);
	void changeColor(Figure *that, const sf::Color &color);
	void setOrigin();
	bool canMoveToThisPlace(int i, int j);
	bool logic(int i, int j);

	bool isMove = false;
	bool isFirsTimeMoving = true;
	std::string _name;
	std::string _color;

	//friend class Field;

protected:

};

