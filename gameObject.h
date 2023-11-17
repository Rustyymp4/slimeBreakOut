#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <map>

typedef enum CollisionSide 
{
	None,

	Right,
	Left,
	Up,
	Down,

	WinRight,
	WinLeft,
	WinUp,
	Out,
};

class gameObject
{
public:
	float positionX;
	float positionY;

	float directionX;
	float directionY;	

	float speed;

	int sizeX;
	int sizeY;

	int radius;

	int hp;

	static std::map <int, sf::Color> ColorList;

	sf::Shape* pShape;
	sf::RenderWindow* window;

	gameObject(float positionX, float positionY, int sizeX, int sizeY, int hp, sf::RenderWindow*);
	gameObject(float positionX, float positionY, int radius, sf::RenderWindow*);

	void draw();
	void setDirection(float dX, float dY);
	void multiplyDirection(float dX, float dY);
	void move(float fDeltaTime);
	CollisionSide hasCollision(gameObject* otherObject, int width, int height);
	void setPosition(float x, float y);
	float getAngle(float dx, float dy);
	void lookAt(float angle);
	void setOrigin(float x, float y);
	void decreaseHP();
};

