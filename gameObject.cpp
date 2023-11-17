#include "gameObject.h"
#include <iostream>

std::map <int, sf::Color> gameObject::ColorList =
{
	{1,sf::Color::Cyan},
	{2,sf::Color::Blue},
	{3,sf::Color::Green},
	{4,sf::Color::Yellow},
	{5,sf::Color::Red},

	{6,sf::Color::White},
};


gameObject::gameObject(float positionX, float positionY, int sizeX, int sizeY, int hp, sf::RenderWindow* window)
{
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->window = window;
	this->pShape = pShape;
	this->speed = 500.f;
	this->hp = hp;

	srand(positionX - positionY);
	int r = rand() % 255;
	int g = rand() % 255;
	int b = rand() % 255;

	pShape = new sf::RectangleShape(sf::Vector2f(sizeX, sizeY));
	pShape->setFillColor(gameObject::ColorList[hp]);

	pShape->setOutlineThickness(2);
	pShape->setOutlineColor(sf::Color(255, 255, 255));

	setPosition(positionX, positionY);
}


gameObject::gameObject(float positionX, float positionY, int radius, sf::RenderWindow* window)
{
	this->radius = radius;
	this->window = window;
	this->pShape = pShape;
	this->speed = 500.f;


	pShape = new sf::CircleShape(radius);
	pShape->setFillColor(sf::Color(240, 153, 240));

	setPosition(positionX, positionY);
}

void gameObject::draw()
{

	window->draw(*pShape);

}

void gameObject::move(float fDeltaTime)
{
	float fNewX = positionX + ( directionX * speed * fDeltaTime );
	float fNewY = positionY + ( directionY * speed * fDeltaTime );

	setPosition(fNewX, fNewY);
}

void gameObject::setPosition(float x, float y)
{
	positionX = x;
	positionY = y;
	pShape->setPosition(x, y);

}

void gameObject::decreaseHP()
{

	this->hp = hp - 1;

}

void normalize(float& dX, float& dY) // MATHS
{
	float fMagnitude = sqrtf((dX) * (dX)+(dY) * (dY));

	dX = dX / fMagnitude;
	dY = dY / fMagnitude;
}

void gameObject::setDirection(float dX, float dY)
{
	normalize(dX, dY);

	directionX = dX;
	directionY = dY;
}

void gameObject::multiplyDirection(float dX, float dY) // MATHS
{
	directionX *= dX;	
	directionY *= dY;
}

bool IsInsideInterval(int v, int vMin, int vMax)
{
	return (v >= vMin && v <= vMax);
}

float gameObject::getAngle(float dx, float dy) // MATHS
{
	const float PI = 3.14159265; 

	float pointX = dx;
	float pointY = positionY;

	float adjacent = pointX - positionX;
	float opposite = pointY - dy;

	float rotation = -(atan2(opposite, adjacent)) * 180 / PI;

	return rotation;
}

void gameObject::lookAt(float angle)
{
	pShape->setRotation(angle);
}

void gameObject::setOrigin(float x, float y)
{
	pShape->setOrigin(x, y);
}

CollisionSide gameObject::hasCollision(gameObject* otherObject, int width, int height)
{
	float X1Min = this->positionX;
	float Y1Min = this->positionY;
	float X1Max = X1Min + this->radius*2;
	float Y1Max = Y1Min + this->radius*2;


	float X2Min = otherObject->positionX;
	float Y2Min = otherObject->positionY;
	float X2Max = X2Min + otherObject->sizeX;
	float Y2Max = Y2Min + otherObject->sizeY;


	bool isXMinInside = IsInsideInterval(X1Min, X2Min, X2Max);
	bool isXMaxInside = IsInsideInterval(X1Max, X2Min, X2Max);
	bool isYMinInside = IsInsideInterval(Y1Min, Y2Min, Y2Max);
	bool isYMaxInside = IsInsideInterval(Y1Max, Y2Min, Y2Max);

	//On tappe le block par le bas
	if (isYMinInside && isXMinInside && isXMaxInside)
	{
		std::cout << "Down" << std::endl;
		return CollisionSide::Down;
	}

	//On tappe le block par le haut
	if (isYMaxInside && (isXMinInside && isXMaxInside))
	{
		std::cout << "Up" <<  std::endl;
		return CollisionSide::Up;
	}

	//On tappe le block par la droite
	if (isXMinInside && isYMaxInside && isYMinInside)
	{
		std::cout << "Right" << std::endl;
		return CollisionSide::Right;

	}

	//On tappe le block par la gauche
	if (isXMaxInside && isYMaxInside && isYMinInside)
	{
		std::cout << "Left" << std::endl;
		return CollisionSide::Left;
	}

	//On tappe le bas de la fenetre
	if (this->positionY >= height)
	{
		std::cout << "Out" << std::endl;
		return CollisionSide::Out;

	}

	//On tappe le haut de la fenetre
	if (this->positionY <= 0)
	{
		std::cout << "WinUp" << std::endl;
		return CollisionSide::WinUp;

	}

	//On tappe la droite de la fenetre
	if (this->positionX >= width - radius*2)
	{
		std::cout << "WinRight" << std::endl;
		return CollisionSide::WinRight;

	}

	//On tappe la gauche de la fenetre
	if (this->positionX <= 0)
	{
		std::cout << "WinLeft" << std::endl;
		return CollisionSide::WinLeft;

	}

	

	return CollisionSide::None;
}

