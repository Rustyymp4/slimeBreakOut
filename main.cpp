#include <SFML/Graphics.hpp>
#include "gameObject.h"
#include "textureManager.h"
#include <windows.h>
#include <iostream>
#include <vector>







int main(int argc, char** argv)
{
	//hide window
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE); //SW_HIDE for hinding, SW_NORMAL for showing

	//Création d'une fenêtre
	int width = 640;
	int height = 900;

	sf::RenderWindow oWindow(sf::VideoMode(width, height), "SFML");

    //Sizes
	int canonSizeX = 50;
	int canonSizeY = 30;
	int ballRadius = 8;

    int offsetY = 80;
    int offsetX = 53;
    int level = 0;
    

    std::vector<gameObject*> objectGrid;
    std::vector<textureManager*> textureGrid;
     
    
	// Level 0
    if (level == 0){

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {

				int posY = i * 23 + offsetY;
				int posX = j * 53 + offsetX;

				int setHP = rand() % 5 + 1;

				objectGrid.push_back(new gameObject(posX, posY, 50, 20, setHP, &oWindow));
				textureGrid.push_back(new textureManager(&oWindow));

			}
		}
        level = 1;

    }
	int lifeCount = 5;


	int tabLength = objectGrid.size();

	gameObject* oCircle = new gameObject((width / 2), height - (height / 8), ballRadius, &oWindow);

    sf::Texture ballTexture;
    sf::Sprite ballSprite;
    ballTexture.loadFromFile("ball.png");
    ballSprite.setTexture(ballTexture);

	gameObject* canon = new gameObject((width / 2) - (canonSizeX / 4), height - (height / 8), canonSizeX, canonSizeY, 1, &oWindow);

    sf::Texture canonTexture;
    sf::Sprite canonSprite;
    canonTexture.loadFromFile("canon.png");
    canonSprite.setTexture(canonTexture);

    //GameLoop
    sf::Clock oClock;
    float fDeltaTime;
    bool ballShot = 0;
    bool ballExist = 0;
 
    int test;
    float mX;
    float mY;
    while (oWindow.isOpen())
    {

        //Table


        fDeltaTime = oClock.restart().asSeconds();

        //EVENT
        sf::Event oEvent;
        while (oWindow.pollEvent(oEvent))
        {
            if (oEvent.type == sf::Event::Closed)
                oWindow.close();
        }

		//UPDATE

		mX = sf::Mouse::getPosition(oWindow).x;
		mY = sf::Mouse::getPosition(oWindow).y;
		float rotation = canon->getAngle(mX, mY);

		if (25 < (rotation + 180) && (rotation + 180) < 150) {
			

			canon->setOrigin(0, 15);
			canon->lookAt(rotation);

            canonSprite.setPosition(canon->positionX, canon->positionY);
            canonSprite.setOrigin(0, 15);
            canonSprite.setRotation(rotation);


			if (ballShot == 0 && lifeCount != 0)
			{
				float fX = oCircle->positionX;
				float fY = oCircle->positionY;
				float directionX = mX - fX;
				float directionY = mY - fY;

				oCircle->setPosition(((width / 2) - (canonSizeX / 4)) - ballRadius, (height - (height / 8)));
				oCircle->setDirection(directionX - ballRadius, directionY);
             
			}
		}

		if (oEvent.type == sf::Event::MouseButtonPressed)
		{
			if (oEvent.mouseButton.button == sf::Mouse::Left && ballShot == 0 && lifeCount != 0)
			{
				ballShot = 1;
				ballExist = 1;
			}
		}


        if (ballShot == 1) 
        {
            //move
            oCircle->move(fDeltaTime);
            ballSprite.setPosition(oCircle->positionX, oCircle->positionY);


            for (int i = 0; i < tabLength; i++)
            {
                if (objectGrid[i] != nullptr)
                {

                    CollisionSide eCollisionSide = oCircle->hasCollision(objectGrid[i], width, height);

                    if (eCollisionSide == CollisionSide::Up || eCollisionSide == CollisionSide::Down)
                    {
                        if (eCollisionSide == CollisionSide::Up)
                        {
                            oCircle->positionY -= 10;
                        }
                        if (eCollisionSide == CollisionSide::Down)
                        {
                            oCircle->positionY += 10;
                        }
                        oCircle->multiplyDirection(1, -1);

                        objectGrid[i]->decreaseHP();
                        if (objectGrid[i]->hp == 0)
                        {

                            objectGrid.erase(objectGrid.begin() + i);
                            tabLength = objectGrid.size();

                        }
                        
                    }
                    if (eCollisionSide == CollisionSide::Left || eCollisionSide == CollisionSide::Right)
                    {

                        if (eCollisionSide == CollisionSide::Up)
                        {
                            oCircle->positionY -= 10;
                        }
                        if (eCollisionSide == CollisionSide::Down)
                        {
                            oCircle->positionY += 10;
                        }
                        oCircle->multiplyDirection(-1, 1);

                        objectGrid[i]->decreaseHP();
                        if (objectGrid[i]->hp == 0)
                        {

                            objectGrid.erase(objectGrid.begin() + i);
                            tabLength = objectGrid.size();

                        }
                    }


                }
            }
            
            CollisionSide eCollisionWindow = oCircle->hasCollision(oCircle, width, height);

            if (eCollisionWindow == CollisionSide::WinUp)
                {
                oCircle->multiplyDirection(1, -1);
                }

            if (eCollisionWindow == CollisionSide::WinLeft || eCollisionWindow == CollisionSide::WinRight)
                {
                oCircle->multiplyDirection(-1, 1);
                }

            if (eCollisionWindow == CollisionSide::Out)
                {
                ballShot = 0;
                ballExist = 0;
                lifeCount -= 1;
                std::cout << lifeCount << std::endl;

            } 
            
            
            
        }


		if (ballShot == 0) {

			// Level 1
			if (level == 1 && tabLength == 0) {

				for (int i = 0; i < 3; i++) {

					for (int j = 0; j < 5; j++) {


						int posY = i * 23 + offsetY;
						int posX = j * 53 + offsetX;

						int setHP = rand() % 5 + 1;

						objectGrid.push_back(new gameObject(posX, posY, 50, 20, setHP, &oWindow));
						textureGrid.push_back(new textureManager(&oWindow));

					}
				}
				level = 2;
				lifeCount = 6;


				tabLength = objectGrid.size();
			}

			// Level 2
			if (level == 2 && tabLength == 0) {

				for (int i = 0; i < 6; i++) {

					for (int j = 0; j < 8; j++) {


						int posY = i * 23 + offsetY;
						int posX = j * 53 + offsetX;

						int setHP = rand() % 5 + 1;

						objectGrid.push_back(new gameObject(posX, posY, 50, 20, setHP, &oWindow));
						textureGrid.push_back(new textureManager(&oWindow));

					}
				}
				level = 3;
				lifeCount = 15;


				tabLength = objectGrid.size();
			}


			// Level 3
			if (level == 3 && tabLength == 0) {

				for (int i = 0; i < 10; i++) {

					for (int j = 0; j < 10; j++) {


						int posY = i * 23 + offsetY;
						int posX = j * 53 + offsetX;

						int setHP = rand() % 5 + 1;

						objectGrid.push_back(new gameObject(posX, posY, 50, 20, setHP, &oWindow));
						textureGrid.push_back(new textureManager(&oWindow));

					}
				}
				level = 4;
				lifeCount = 20;


				tabLength = objectGrid.size();
			}

			// Level 4
			if (level == 4 && tabLength == 0) {

				for (int i = 0; i < 10; i++) {

					for (int j = 0; j < 10; j++) {


						int posY = i * 23 + offsetY;
						int posX = j * 53 + offsetX;

						int setHP = rand() % 5 + 1;

						objectGrid.push_back(new gameObject(posX, posY, 50, 20, setHP, &oWindow));
						textureGrid.push_back(new textureManager(&oWindow));

					}
				}
				level = 4;
				lifeCount = 20;


				tabLength = objectGrid.size();

                if (level == 4 && tabLength == 0)
                {

                    sf::Texture winTexture;
                    sf::Sprite winSprite;
                    winTexture.loadFromFile("WinScreen.png");
                    winSprite.setTexture(winTexture);

                    oWindow.draw(winSprite);

                }
			}
		}
        

        //DRAW
        oWindow.clear();
   
        for (int i = 0; i < tabLength; i++)
        {
            textureGrid[i]->setTexture(objectGrid[i]->hp, objectGrid[i]->positionX, objectGrid[i]->positionY);
            textureGrid[i]->draw();
            textureGrid[i]->rescale(2, 2);
        }


        if (ballExist == 1) 
        {
            oWindow.draw(ballSprite);
        }

        if (lifeCount == 0)
        {

            sf::Texture loseTexture;
            sf::Sprite loseSprite;
            loseTexture.loadFromFile("LoseScreen.png");
            loseSprite.setTexture(loseTexture);

            oWindow.draw(loseSprite);

        }
       
        if (tabLength != 0 && lifeCount != 0)
        {
            oWindow.draw(canonSprite);
        }
        

        oWindow.display();

        
    }
    delete[] &objectGrid;
    return 0;
}

