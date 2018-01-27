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

private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	sf::Image _image;
	sf::Texture _texture;
	sf::Sprite _sprite;
};

