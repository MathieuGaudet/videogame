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

	playerLocation.x = startLocationX;
	playerLocation.y = startLocationY;
	getMapLayout(7, 7);
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
