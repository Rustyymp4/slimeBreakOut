#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>

class textureManager
{
public:
	sf::Texture rectTexture;
	sf::Sprite rectSprite;
	
	sf::RenderWindow* window;

	textureManager(sf::RenderWindow*);
	void setTexture(int hp, float posX, float posY);
	void draw();
	void rescale(int x, int y);
};