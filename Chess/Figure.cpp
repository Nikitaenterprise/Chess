#include "Figure.h"
#include "Game.h"

Figure::Figure(const std::string &name, const std::string &color)
{
	_name = name;
	_color = color;

	_image.loadFromFile("../Chess/Images/"+_name+".png");

	_texture.loadFromImage(_image);
	_sprite.setTexture(_texture);

	_sprite.setTextureRect(sf::IntRect(_color == "w" ? 0 : _image.getSize().x / 2, 0, _image.getSize().x / 2, _image.getSize().y));
	_sprite.setScale(float(0.2), float(0.2));
}

//Figure::~Figure()
//{
//	std::cout << this->_name << std::endl;
//	std::cout << this->_color << std::endl;
//	std::cout << this << std::endl;
//	//delete this;
//}

void Figure::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}

void Figure::processEvents(sf::Event &event, const sf::Window &window)
{
	if (event.type ==
		sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Left &&
		this->_sprite.getGlobalBounds().contains(static_cast<sf::Vector2f> (sf::Mouse::getPosition(window))) &&
		this->isMove == false)
	{
		this->_oldPos = this->_sprite.getPosition();
	}
	if (event.type == 
		sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Left ||
		event.type == sf::Event::MouseMoved && this->isMove)
	{
		if (this->_sprite.getGlobalBounds().contains(static_cast<sf::Vector2f> (sf::Mouse::getPosition(window))))
		{
			this->isMove = true;
			this->isFirsTimeMoving = false;
			this->dPos = sf::Vector2f(0, 0);
			this->dPos = static_cast<sf::Vector2f> (sf::Mouse::getPosition(window)) -
							this->pos - sf::Vector2f(this->_sprite.getGlobalBounds().width/2, this->_sprite.getGlobalBounds().height / 2);
			changeColor(this, sf::Color::Green);
		}
	}
	if (event.type ==
		sf::Event::MouseButtonReleased &&
		event.mouseButton.button == sf::Mouse::Left)
	{
		if (this->_sprite.getGlobalBounds().contains(static_cast<sf::Vector2f> (sf::Mouse::getPosition(window)))
			&& this->isMove)
		{
			this->isMove = false;
			changeColor(this, sf::Color::White);
			int i = int(sf::Mouse::getPosition(window).x) / 100, j = int(sf::Mouse::getPosition(window).y) / 100;
			if (_thisGame->getBoardElement(i, j).front() == this->_color.front())
			{
				this->_sprite.setPosition(this->_oldPos.x, this->_oldPos.y);	
			}
			if(_thisGame->getBoardElement(i, j).front() != this->_color.front()
				&& _thisGame->getBoardElement(i, j) != "empty")
			{
				_thisGame->setBoardElement(int(this->_oldPos.x / 100), int(this->_oldPos.y / 100), std::string("empty"));
				_thisGame->deleteFigure(&_thisGame->getBoardFigure(i, j));
				_thisGame->setBoardElement(i, j, std::string("empty"));

			}
			if (_thisGame->getBoardElement(i, j) == "empty")
			{
				_thisGame->setBoardElement(int(this->_oldPos.x / 100), int(this->_oldPos.y / 100), std::string("empty"));
				this->_sprite.setPosition(sf::Vector2f(i * 100, j * 100));
				this->_newPos = this->_sprite.getPosition();
				_thisGame->setBoardElement(i, j, this->_color + this->_name);
			}
			std::cout << logic(i, j) << std::endl;
			this->_oldPos = this->_sprite.getPosition();
			_thisGame->printBoard();
		}
	}
}

void Figure::update()
{
	if (isMove)
	{
		this->pos += this->dPos;
		this->_sprite.setPosition(this->pos);
		this->dPos = sf::Vector2f(0, 0);
	}
}

void Figure::updateCoordinates(sf::Vector2i &pos)
{
	
}

void Figure::changeColor(Figure *that, const sf::Color &color)
{
	that->_sprite.setColor(color);
}

void Figure::setOrigin()
{
	_sprite.setOrigin(sf::Vector2f());
}

bool Figure::canMoveToThisPlace(int i, int j)
{
	if (_thisGame->getBoardElement(i, j) == "empty") return true;
	else return false;
}

bool Figure::logic(int i, int j)
{
	bool canMove = false;
	int colorVariable = 1;
	int iOld = static_cast<int> (this->_oldPos.x / 100);
	int jOld = static_cast<int> (this->_oldPos.y / 100);

	if (this->_color == "w") colorVariable *= -1;

	if (this->_name == "pawn")
	{
		if (i - iOld == 0 && j - jOld == -1 * colorVariable) canMove = true;
		else if ((i - iOld == -1 * colorVariable || i - iOld == 1 * colorVariable)
				&& j - jOld == -1 * colorVariable) canMove = true;
	}
	if (this->_name == "king")
	{
		if (i - iOld == 0 && j - jOld == -1 * colorVariable) canMove = true;
		else if (i - iOld == 1 * colorVariable && j - jOld == -1 * colorVariable) canMove = true;
		else if (i - iOld == 1 * colorVariable && j - jOld == 0) canMove = true;
		else if (i - iOld == 1 * colorVariable && j - jOld == 1 * colorVariable) canMove = true;
		else if (i - iOld == 0 && j - jOld == 1 * colorVariable) canMove = true;
		else if (i - iOld == -1 * colorVariable && j - jOld == 1 * colorVariable) canMove = true;
		else if (i - iOld == -1 * colorVariable && j - jOld == 0) canMove = true;
		else if (i - iOld == -1 * colorVariable && j - jOld == -1 * colorVariable) canMove = true;
	}
	if (this->_name == "knight")
	{
		if (i - iOld == 1 * colorVariable && j - jOld == -2 * colorVariable) canMove = true;
		else if (i - iOld == 2 * colorVariable && j - jOld == -1 * colorVariable) canMove = true;
		else if (i - iOld == 2 * colorVariable && j - jOld == 1 * colorVariable) canMove = true;
		else if (i - iOld == 1 * colorVariable && j - jOld == 2 * colorVariable) canMove = true;
		else if (i - iOld == -1 * colorVariable && j - jOld == 2 * colorVariable) canMove = true;
		else if (i - iOld == -2 * colorVariable && j - jOld == 1 * colorVariable) canMove = true;
		else if (i - iOld == -2 * colorVariable && j - jOld == -1 * colorVariable) canMove = true;
		else if (i - iOld == -1 * colorVariable && j - jOld == -2 * colorVariable) canMove = true;
	}
	if (this->_name == "castle")
	{
		if (7 - i >= 0 && j - jOld == 0) canMove = true;
		else if (i - iOld == 0 && 7 - j >= 0) canMove = true;
	}
	if (this->_name == "bishop")
	{
		if (7 - i >= 0 && 7 - j >= 0) canMove == true;
	}
	std::cout << "iOld = " << iOld << "\tjOld = " << jOld
		<< "\ti = " << i << "\tj = " << j << std::endl;
	std::cout << "j - jOld = " << j - jOld << "\ti - iOld = " << i - iOld << std::endl;
	std::cout << "7 - i = " << 7 - i << "\t7 - j = " << 7 - j << std::endl;
	return canMove;
}