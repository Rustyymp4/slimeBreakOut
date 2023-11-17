#include "textureManager.h"
#include <iostream>

textureManager::textureManager(sf::RenderWindow* window)
{

	this->window = window;

	sf::Texture rectTexture;
	sf::Sprite rectSprite;
};

void textureManager::setTexture(int hp, float posX, float posY)
{
	if (hp == 1)
	{
		rectTexture.loadFromFile("one.png");
		rectSprite.setTexture(rectTexture);


	}
	else if (hp == 2)
	{
		rectTexture.loadFromFile("two.png");
		rectSprite.setTexture(rectTexture);
	}
	else if (hp == 3)
	{
		rectTexture.loadFromFile("three.png");
		rectSprite.setTexture(rectTexture);
	}
	else if (hp == 4)
	{
		rectTexture.loadFromFile("four.png");
		rectSprite.setTexture(rectTexture);
	}
	else if (hp == 5)
	{
		rectTexture.loadFromFile("five.png");
		rectSprite.setTexture(rectTexture);
	}
	else if (hp == 6)
	{
		rectTexture.loadFromFile("six.png");
		rectSprite.setTexture(rectTexture);
	}

	rectSprite.setPosition(posX, posY);
	
}

void textureManager::draw()
{

	window->draw(rectSprite);

}

void textureManager::rescale(int x, int y)
{

	rectSprite.setScale(x, y);


}