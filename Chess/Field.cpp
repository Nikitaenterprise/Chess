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
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			for (auto it = _fieldElement.begin(); it != _fieldElement.end(); it++)
			{
				std::cout << "i = " << i << "\ti % 2 = " << i % 2 << "\t";
				std::cout << "j = " << j << "\tj % 2 = " << j % 2 << std::endl;

				if (i % 2 == 0)	(*it)->setFillColor(sf::Color::White);
				else if (i % 2 != 0) (*it)->setFillColor(sf::Color::Black);
				(*it)->setPosition(sf::Vector2f(i * 800 / 8, j * 800 / 8));
			}
		}
	}
}

Field::~Field()
{
}

void Field::processEvents()
{
	isClicked = sf::Mouse::isButtonPressed(sf::Mouse::Left);
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
