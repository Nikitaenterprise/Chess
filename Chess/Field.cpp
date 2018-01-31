#include "Field.h"

Field::Field()
{
	/*_image.loadFromFile("../Chess/Images/chessboard.png");
	_texture.loadFromImage(_image);
	_sprite.setTexture(_texture);
	std::cout << "hi\n";*/
	for (int i = 0; i < 8*8; i++)
	{
		_fieldElement.push_back(new sf::RectangleShape(sf::Vector2f(800 / 8, 800 / 8)));
	}
	
	int i = 0, j = 0;
	int inverse = -1;
	for (auto it = _fieldElement.begin(); it != _fieldElement.end(); it++)
	{
		if (inverse == 1)
		{
			if (i % 2 == 0)	(*it)->setFillColor(sf::Color::Black);
			else if (i % 2 != 0) (*it)->setFillColor(sf::Color::White);
		}
		else if (inverse == -1)
		{
			if (i % 2 == 0)	(*it)->setFillColor(sf::Color::White);
			else if (i % 2 != 0) (*it)->setFillColor(sf::Color::Black);
		}
		(*it)->setPosition(sf::Vector2f(i * 800 / 8, j * 800 / 8));

		i++;
		if (i % 8 == 0)
		{
			j++;
			i = 0;
			inverse *= -1;
		}
	}
}

Field::~Field()
{
}

void Field::processEvents(sf::Event &event)
{
	isClicked = sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

void Field::update()
{
}

void Field::update(sf::Time deltaTime)
{

}

void Field::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (auto it = _fieldElement.begin(); it != _fieldElement.end(); it++)
	{
		target.draw(*(*it), states);
	}
}
