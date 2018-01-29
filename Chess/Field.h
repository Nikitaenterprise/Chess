#pragma once
#include <SFML\Graphics.hpp>

class Field : public sf::Drawable
{
public:
	Field(const Field &) = delete;
	Field & operator=(const Field &) = delete;
	Field();
	~Field();

	void processEvents();
	void update(sf::Time deltaTime);
	void setScale(const sf::Vector2f &vec);
	sf::Vector2u getSizeOfTexture();
	void setSpriteFromTexture(const sf::Texture &texture);
	void setStartPosition(const sf::Vector2f &vec);
	bool isClicked;
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states = sf::RenderStates::Default) const override;

protected:
	sf::Image _image;
	sf::Texture _texture;
	sf::Sprite _sprite;
};

