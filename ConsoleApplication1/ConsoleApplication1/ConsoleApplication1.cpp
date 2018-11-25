// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "pch.h"
#include <stdlib.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include "DungeonMap.h"

struct location
{
	int x;
	int y;
};

int main()
{
	struct location playerLocation;
	int displayedSection[15][15];

	playerLocation.x = startLocationX;
	playerLocation.y = startLocationY;
	

	sf::RenderWindow window(sf::VideoMode(32*15, 32*15), "SFML works!");

	sf::Texture playerFrontTexture;
	if (!playerFrontTexture.loadFromFile("C:\\Users\\Gaudets\\Documents\\repos\\videogame\\sprites\\KnightMagic.png"))
	{
		std::cout << "error: Image not found";
	}
	
	sf::Texture wallTexture;
	if (!wallTexture.loadFromFile("C:\\Users\\Gaudets\\Documents\\repos\\videogame\\sprites\\Wall.png"))
	{
		std::cout << "error: Image not found";
	}

	sf::Texture wallShadowTexture;
	if (!wallShadowTexture.loadFromFile("C:\\Users\\Gaudets\\Documents\\repos\\videogame\\sprites\\WallShadow.png"))
	{
		std::cout << "error: Image not found";
	}

	sf::Texture floorTexture;
	if (!floorTexture.loadFromFile("C:\\Users\\Gaudets\\Documents\\repos\\videogame\\sprites\\Floor.png"))
	{
		std::cout << "error: Image not found";
	}

	sf::Texture blankTexture;
	if (!blankTexture.loadFromFile("C:\\Users\\Gaudets\\Documents\\repos\\videogame\\sprites\\Blank.png"))
	{
		std::cout << "error: Image not found";
	}

	sf::Sprite dungeonMapLayout[15][15];

	for (int y = 0; y < 15; y++)
	{
		for (int x = 0; x < 15; x++) {
			dungeonMapLayout[y][x].setPosition(sf::Vector2f((float)(x * 32), (float)(y * 32)));
		}
	}
	
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		getMapLayout(playerLocation.x, playerLocation.y, displayedSection);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if (displayedSection[7][6]==0xe0)
			{
				playerLocation.x--;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (displayedSection[7][8] == 0xe0)
			{
				playerLocation.x++;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			if (displayedSection[6][7] == 0xe0)
			{
				playerLocation.y--;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if (displayedSection[8][7] == 0xe0)
			{
				playerLocation.y++;
			}
		}
		window.clear();
		//std::cout << "\n";
		for (int y = 0; y < 15; y++)
		{
			for (int x = 0; x < 15; x++) {
				// Set texture and location on the screen
				switch (displayedSection[y][x])
				{
				/*case 0xff:
					dungeonMapLayout[y][x].setTexture(blankTexture);
					break;*/
				case 0x00:
					dungeonMapLayout[y][x].setTexture(wallTexture);
					//std::cout << "[]";
					break;
				case 0x92:
					dungeonMapLayout[y][x].setTexture(wallShadowTexture);
					//std::cout << "()";
					break;
				case 0xe0:
					dungeonMapLayout[y][x].setTexture(floorTexture);
					//std::cout << "00";
					break;

				default:
					dungeonMapLayout[y][x].setTexture(blankTexture);
					//std::cout << "@@";
					break;
				}
				
				window.draw(dungeonMapLayout[y][x]);
				
			}

			//std::cout << "\n";
		}
		dungeonMapLayout[7][7].setTexture(playerFrontTexture);
		window.draw(dungeonMapLayout[7][7]);
		window.display();
		Sleep(100);
//		std::cout << "\n";
	}

	return 0;
}





#if 0
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

	sf::Sprite knightSprite;
	knightSprite.setPosition(sf::Vector2f(10.f, 50.f)); // absolute position


	sf::Texture textureLeft1;
	if (!textureLeft1.loadFromFile("C:\\Users\\Gaudets\\Documents\\repos\\videogame\\sprites\\knightLeft1.png"))
	{
		std::cout << "error: Image not found";
	}

	sf::Texture textureLeft2;
	if (!textureLeft2.loadFromFile("C:\\Users\\Gaudets\\Documents\\repos\\videogame\\sprites\\knightLeft2.png"))
	{
		std::cout << "error: Image not found";
	}

	sf::Texture textureLeft3;
	if (!textureLeft3.loadFromFile("C:\\Users\\Gaudets\\Documents\\repos\\videogame\\sprites\\knightLeft3.png"))
	{
		std::cout << "error: Image not found";
	}


	sf::Texture textureRight1;
	if (!textureRight1.loadFromFile("C:\\Users\\Gaudets\\Documents\\repos\\videogame\\sprites\\knightRight1.png"))
	{
		std::cout << "error: Image not found";
	}

	sf::Texture textureRight2;
	if (!textureRight2.loadFromFile("C:\\Users\\Gaudets\\Documents\\repos\\videogame\\sprites\\knightRight2.png"))
	{
		std::cout << "error: Image not found";
	}

	sf::Texture textureRight3;
	if (!textureRight3.loadFromFile("C:\\Users\\Gaudets\\Documents\\repos\\videogame\\sprites\\knightRight3.png"))
	{
		std::cout << "error: Image not found";
	}


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		while (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{


			knightSprite.setTexture(textureLeft1);
			knightSprite.move(-1.f, 0.f);
			window.draw(knightSprite);
			window.display();
			Sleep(250);
			window.clear();

			knightSprite.setTexture(textureLeft2);
			knightSprite.move(-1.f, 0.f);
			window.draw(knightSprite);
			window.display();
			Sleep(250);
			window.clear();

			knightSprite.setTexture(textureLeft3);
			knightSprite.move(-1.f, 0.f);
			window.draw(knightSprite);
			window.display();
			Sleep(250);
			window.clear();

			knightSprite.setTexture(textureLeft2);
			knightSprite.move(-1.f, 0.f);
			window.draw(knightSprite);
			window.display();
			Sleep(250);
			window.clear();
		}


		while (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{

			knightSprite.setTexture(textureRight1);
			knightSprite.move(1.f, 0.f);
			window.draw(knightSprite);
			window.display();
			Sleep(175);
			knightSprite.move(1.f, 0.f);
			Sleep(175);
			window.clear();

			knightSprite.setTexture(textureRight2);
			knightSprite.move(1.f, 0.f);
			window.draw(knightSprite);
			window.display();
			Sleep(175);
			knightSprite.move(1.f, 0.f);
			Sleep(175);
			window.clear();

			knightSprite.setTexture(textureRight3);
			knightSprite.move(1.f, 0.f);
			window.draw(knightSprite);
			window.display();
			Sleep(175);
			knightSprite.move(1.f, 0.f);
			Sleep(175);
			window.clear();

			knightSprite.setTexture(textureRight2);
			knightSprite.move(1.f, 0.f);
			window.draw(knightSprite);
			window.display();
			Sleep(175);
			knightSprite.move(1.f, 0.f);
			Sleep(175);
			window.clear();
		}

		//window.draw(shape);

	}
#endif
