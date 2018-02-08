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
	//std::cout << _sprite.getLocalBounds().width << "\t" << _sprite.getLocalBounds().height << std::endl;
	//_sprite.setOrigin(sf::Vector2f( pos.x + _image.getSize().x / 4, pos.y + _image.getSize().y / 2));
}

Figure::~Figure()
{
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
		std::cout << "_oldPos0 = " << this->_oldPos.x << " ( " << int(this->_oldPos.x / 100) << " ) "
			<< "\t" << this->_oldPos.y << " ( " << int(this->_oldPos.y / 100) << " ) " << std::endl;
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
			sf::Vector2f temp(_image.getSize().x / 4, _image.getSize().y / 2);
			this->dPos = static_cast<sf::Vector2f> (sf::Mouse::getPosition(window)) -
							this->pos - sf::Vector2f(this->_sprite.getGlobalBounds().width/2, this->_sprite.getGlobalBounds().height / 2);
			changeColor(this, sf::Color::Green);
			/*std::cout << "(" << dPos.x << ", " << dPos.y << ")\t=\t(" 
				<< sf::Mouse::getPosition(window).x << ", " << sf::Mouse::getPosition(window) .y << ")\t-\t(" 
				<< this->pos.x << ", " << this->pos.y << ")\t-\t("
				<< this->_sprite.getGlobalBounds().width / 2 << ", " << this->_sprite.getGlobalBounds().height / 2 << ")"
				<<std::endl;
			std::cout << "(dPos.x, dPos.y)\t=\t(mouse.x, mouse.y)\t-\t(pos.x, pos.y)\t-\t(bounds.width / 2, bounds.height / 2)\n";*/
		}
	}
	else if (event.type ==
		sf::Event::MouseButtonReleased &&
		event.mouseButton.button == sf::Mouse::Left)
	{
		if (this->_sprite.getGlobalBounds().contains(static_cast<sf::Vector2f> (sf::Mouse::getPosition(window))))
		{
			this->isMove = false;
			changeColor(this, sf::Color::White);
			int i = int(sf::Mouse::getPosition(window).x) / 100, j = int(sf::Mouse::getPosition(window).y) / 100;
			if (this->canMoveToThisPlace(i, j))
			{
				this->_sprite.setPosition(sf::Vector2f(i * 100, j * 100));
				_thisGame->setBoardElement(int(this->_oldPos.x / 100), int(this->_oldPos.y / 100), std::string("empty"));
				this->_newPos = this->_sprite.getPosition();
				_thisGame->setBoardElement(i, j, this->_color + this->_name);
				_thisGame->printBoard();
			}
			else
			{
				this->_sprite.setPosition(this->_oldPos.x, this->_oldPos.y);
				
				_thisGame->printBoard();
			}
			/*std::cout << "_oldPos = " << this->_oldPos.x << " ( " << int(this->_oldPos.x / 100) << " ) " 
				<< "\t" << this->_oldPos.y << " ( " << int(this->_oldPos.y / 100) << " ) " << std::endl;
			std::cout << "_newPos = " << this->_newPos.x << " ( " << int(this->_newPos.x / 100) << " ) "
				<< "\t" << this->_newPos.y << " ( " << int(this->_newPos.y / 100) << " ) " << std::endl;
			std::cout << std::endl;*/
		}
	}
}

void Figure::update()
{
	if (isMove)
	{
		//this->isMove = false;
		//std::cout << "----------UPDATE----------" << std::endl;
		//std::cout << pos.x << "\t" << pos.y << "\t" << dPos.x << "\t" << dPos.y << "\n";
		this->pos += this->dPos;
		this->_sprite.setPosition(this->pos);
		this->dPos = sf::Vector2f(0, 0);
		//std::cout << pos.x << "\t" << pos.y << "\t" << dPos.x << "\t" << dPos.y << "\n";
		//std::cout << std::endl;
		//_oldPos = this->_sprite.getPosition();

		//this->_sprite.setPosition(100 * int(this->pos.x / 100.0f), 100 * int(this->pos.y / 100.0f));
		/*_newPos = this->_sprite.getPosition();
		
		int i = int(pos.x) / 100;
		int j = int(pos.y) / 100;
		std::cout << i << "\t" << j << std::endl;*/
		
		//this->_sprite.setPosition(this->_sprite.getPosition() + this->dPos);
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
