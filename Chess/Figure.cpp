#include "Figure.h"


//const sf::Vector2i &vec1, const sf::Vector2i &vec2
Figure::Figure(const std::string &name, const std::string &color)
{
	_name = name;
	_color = color;

	_image.loadFromFile("../Chess/Images/"+_name+".png");

	_texture.loadFromImage(_image);
	_sprite.setTexture(_texture);

	_sprite.setTextureRect(sf::IntRect(_color == "white" ? 0 : _image.getSize().x / 2, 0, _image.getSize().x / 2, _image.getSize().y));
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
		event.mouseButton.button == sf::Mouse::Left ||
		event.type == sf::Event::MouseMoved && this->isMove)
	{
		if (this->_sprite.getGlobalBounds().contains(static_cast<sf::Vector2f> (sf::Mouse::getPosition(window))))
		{
			this->isMove = true;
			this->dPos = sf::Vector2f(0, 0);
			sf::Vector2f temp(_image.getSize().x / 4, _image.getSize().y / 2);
			this->dPos = static_cast<sf::Vector2f> (sf::Mouse::getPosition(window)) -
							this->pos - sf::Vector2f(this->_sprite.getGlobalBounds().width/2, this->_sprite.getGlobalBounds().height / 2);
			changeColor(this, sf::Color::Green);
			std::cout << "(" << dPos.x << ", " << dPos.y << ")\t=\t(" 
				<< sf::Mouse::getPosition(window).x << ", " << sf::Mouse::getPosition(window) .y << ")\t-\t(" 
				<< this->pos.x << ", " << this->pos.y << ")\t-\t("
				<< this->_sprite.getGlobalBounds().width / 2 << ", " << this->_sprite.getGlobalBounds().height / 2 << ")"
				<<std::endl;
			std::cout << "(dPos.x, dPos.y)\t=\t(mouse.x, mouse.y)\t-\t(pos.x, pos.y)\t-\t(bounds.width / 2, bounds.height / 2)\n";
		}
	}
	else if (event.type == 
		sf::Event::MouseButtonReleased &&
		event.mouseButton.button == sf::Mouse::Left)
	{
		changeColor(this, sf::Color::White);
		this->isMove = false;
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
		//std::cout << pos.x << "\t" << pos.y << "\t" << dPos.x << "\t" << dPos.y << "\n";
		//std::cout << std::endl;

		sf::Vector2f oldPos = this->_sprite.getPosition();
		sf::Vector2f newPos = this->pos;
		int i = int(oldPos.x) / 100;
		int j = int(oldPos.y) / 100;
		std::cout << i << "\t" << j << std::endl;
		this->_sprite.setPosition(this->pos);
		
		this->dPos = sf::Vector2f(0, 0);
		
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
