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
			if (canMoveHere(i, j))
			{
				move(i, j);
			}
			else this->_sprite.setPosition(this->_oldPos.x, this->_oldPos.y);
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

void Figure::move(int i, int j)
{
	if (_thisGame->getBoardElement(i, j).front() == this->_color.front())
	{
		this->_sprite.setPosition(this->_oldPos.x, this->_oldPos.y);
	}
	if (_thisGame->getBoardElement(i, j).front() != this->_color.front()
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
	this->isFirsTimeMoving = false;
	this->_oldPos = this->_sprite.getPosition();
}

void Figure::changeColor(Figure *that, const sf::Color &color)
{
	that->_sprite.setColor(color);
}

bool Figure::canMoveHere(int i, int j)
{
	enum line { horizontal, vertical, diagonalL, diagonalR };
	bool canMove = false;
	int colorVariable = 1;
	int iOld = static_cast<int> (this->_oldPos.x / 100);
	int jOld = static_cast<int> (this->_oldPos.y / 100);

	if (this->_color == "w") colorVariable *= -1;

	if (this->_name == "pawn")
	{
		if (this->isFirsTimeMoving && i - iOld == 0 && j - jOld == -2 * colorVariable)
		{
			this->isFirsTimeMoving = false;
			canMove = true;
		}
		if (i - iOld == 0 && j - jOld == -1 * colorVariable) canMove = true;
		if ((i - iOld == -1 * colorVariable || i - iOld == 1 * colorVariable)
			&& j - jOld == -1 * colorVariable)
		{
			if (_thisGame->getBoardElement(i, j) != "empty") canMove = true;
		}
	}
	if (this->_name == "king")
	{
		if ((i - iOld == 0 && j - jOld == -1 * colorVariable) 
			||	(i - iOld == 1 * colorVariable && j - jOld == -1 * colorVariable) 
			||	(i - iOld == 1 * colorVariable && j - jOld == 0) 
			||	(i - iOld == 1 * colorVariable && j - jOld == 1 * colorVariable) 
			||	(i - iOld == 0 && j - jOld == 1 * colorVariable) 
			||	(i - iOld == -1 * colorVariable && j - jOld == 1 * colorVariable) 
			||	(i - iOld == -1 * colorVariable && j - jOld == 0) 
			||	(i - iOld == -1 * colorVariable && j - jOld == -1 * colorVariable)) canMove = true;

		switch (i)
		{
		case 2:
			if (this->isFirsTimeMoving && checkLine(i - 1, j, iOld, jOld, line::horizontal))
			{
				_thisGame->getBoardFigure(i - 2, j).move(i + 1, j);
				canMove = true;
			}
			break;
		case 6:
			if (this->isFirsTimeMoving && checkLine(i, j, iOld, jOld, line::horizontal))
			{
				_thisGame->getBoardFigure(i + 1, j).move(i - 1, j);
				canMove = true;
			}
			break;
		}
		
	}
	if (this->_name == "knight")
	{
		if ((i - iOld == 1 * colorVariable && j - jOld == -2 * colorVariable)
			||	(i - iOld == 2 * colorVariable && j - jOld == -1 * colorVariable)
			||	(i - iOld == 2 * colorVariable && j - jOld == 1 * colorVariable)
			||	(i - iOld == 1 * colorVariable && j - jOld == 2 * colorVariable)
			||	(i - iOld == -1 * colorVariable && j - jOld == 2 * colorVariable)
			||	(i - iOld == -2 * colorVariable && j - jOld == 1 * colorVariable)
			||	(i - iOld == -2 * colorVariable && j - jOld == -1 * colorVariable)
			||	(i - iOld == -1 * colorVariable && j - jOld == -2 * colorVariable)) canMove = true;
	}
	if (this->_name == "castle")
	{
		if (j - jOld == 0)
		{
			canMove = true;
			canMove = checkLine(i, j, iOld, jOld, line::horizontal);
		}
		if (i - iOld == 0)
		{
			canMove = true;
			canMove = checkLine(i, j, iOld, jOld, line::vertical);
		}
	}
	if (this->_name == "bishop")
	{
		if (i - iOld == j - jOld)
		{
			canMove = true;
			canMove = checkLine(i, j, iOld, jOld, line::diagonalL);
		}
		if (i - iOld == (j - jOld) * -1
			||	(i - iOld) * -1 == j - jOld)
		{
			canMove = true;
			canMove = checkLine(i, j, iOld, jOld, line::diagonalR);
		}
	}
	if (this->_name == "queen")
	{
		if (j - jOld == 0)
		{
			canMove = true;
			canMove = checkLine(i, j, iOld, jOld, line::horizontal);
		}
		if (i - iOld == 0)
		{
			canMove = true;
			canMove = checkLine(i, j, iOld, jOld, line::vertical);
		}
		if (i - iOld == j - jOld)
		{
			canMove = true;
			canMove = checkLine(i, j, iOld, jOld, line::diagonalL);
		}
		if (i - iOld == (j - jOld) * -1
			||	(i - iOld) * -1 == j - jOld)
		{
			canMove = true;
			canMove = checkLine(i, j, iOld, jOld, line::diagonalR);
		}
	}
	return canMove;
}

bool Figure::checkLine(int i, int j, int iOld, int jOld, int line)
{
	bool canMove = true;
	switch (line)
	{
	case 0:
			if (i < iOld)
			{
				for (int m = i; m < iOld; m++)
				{
						std::cout << "we are here\n";
					if (_thisGame->getBoardElement(i, j) != "empty") break;
					if (_thisGame->getBoardElement(m, j) != "empty")
					{
						canMove = false;
						break;
					}
				}
			}
			if (i > iOld)
			{
				for (int m = i; m > iOld; m--)
				{
					if (_thisGame->getBoardElement(i, j) != "empty") break;
					if (_thisGame->getBoardElement(m, j) != "empty")
					{
						canMove = false;
						break;
					}
				}
			}
		break;
	case 1:
		if (j < jOld)
		{
			for (int m = j; m < jOld; m++)
			{
				if (_thisGame->getBoardElement(i, j) != "empty") break;
				if (_thisGame->getBoardElement(i, m) != "empty")
				{
					canMove = false;
					break;
				}
			}
		}
		if (j > jOld)
		{
			for (int m = j; m > jOld; m--)
			{
				if (_thisGame->getBoardElement(i, j) != "empty") break;
				if (_thisGame->getBoardElement(i, m) != "empty")
				{
					canMove = false;
					break;
				}
			}
		}
		break;
	case 2:
		if (i < iOld && j < jOld)
		{
			for (int m = i, n = j; m < iOld && n < jOld; m++, n++)
			{
				if (_thisGame->getBoardElement(i, j) != "empty") break;
				if (_thisGame->getBoardElement(m, n) != "empty")
				{
					canMove = false;
					break;
				}
			}
		}
		if (i > iOld && j > jOld)
		{
			for (int m = i, n = j; m > iOld && n > jOld; m--, n--)
			{
				if (_thisGame->getBoardElement(i, j) != "empty") break;
				if (_thisGame->getBoardElement(m, n) != "empty")
				{
					canMove = false;
					break;
				}
			}
		}
		break;
	case 3:
		if (i < iOld && j > jOld)
		{
			for (int m = i, n = j; m < iOld && n > jOld; m++, n--)
			{
				if (_thisGame->getBoardElement(i, j) != "empty") break;
				if (_thisGame->getBoardElement(m, n) != "empty")
				{
					canMove = false;
					break;
				}
			}
		}
		if (i > iOld && j < jOld)
		{
			for (int m = i, n = j; m > iOld && n < jOld; m--, n++)
			{
				if (_thisGame->getBoardElement(i, j) != "empty") break;
				if (_thisGame->getBoardElement(m, n) != "empty")
				{
					canMove = false;
					break;
				}
			}
		}
		break;
	}
	
	return canMove;
}
