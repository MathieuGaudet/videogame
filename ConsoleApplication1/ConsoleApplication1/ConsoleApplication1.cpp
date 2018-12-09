// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "pch.h"
#include <stdlib.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include "DungeonMap.h"

// Game specifications
constexpr int dungeonDisplay = 15;
constexpr int spriteSize = 32;
constexpr int displayCenter = dungeonDisplay / 2;
struct location
{
	int x;
	int y;
};

enum characterDirection {
	LEFT = 0,
	RIGHT,
	UP,
	DOWN
};

int main()
{
	struct location playerLocation;
	int displayedSection[dungeonDisplay][dungeonDisplay];

	playerLocation.x = startLocationX;
	playerLocation.y = startLocationY;


	sf::RenderWindow window(sf::VideoMode(spriteSize * dungeonDisplay, spriteSize * dungeonDisplay), "Mathieu's Game");


	//0 = Left, 1 = Right, 2 = Up, 3 = down
	sf::Texture playerTextures[4][3];

	if (!playerTextures[0][0].loadFromFile("sprites/KnightLeft1v2.png"))
	{
		std::cout << "error: Image not found";
	}

	if (!playerTextures[0][1].loadFromFile("sprites/KnightLeft2v2.png"))
	{
		std::cout << "error: Image not found";
	}

	if (!playerTextures[0][2].loadFromFile("sprites/KnightLeft3v2.png"))
	{
		std::cout << "error: Image not found";
	}
	if (!playerTextures[1][0].loadFromFile("sprites/knightRight1v2.png"))
	{
		std::cout << "error: Image not found";
	}
	if (!playerTextures[1][1].loadFromFile("sprites/knightRight2v2.png"))
	{
		std::cout << "error: Image not found";
	}
	if (!playerTextures[1][2].loadFromFile("sprites/knightRight3v2.png"))
	{
		std::cout << "error: Image not found";
	}
	if (!playerTextures[2][0].loadFromFile("sprites/knightUp1.png"))
	{
		std::cout << "error: Image not found";
	}
	if (!playerTextures[2][1].loadFromFile("sprites/knightUp2.png"))
	{
		std::cout << "error: Image not found";
	}
	if (!playerTextures[2][2].loadFromFile("sprites/knightUp3.png"))
	{
		std::cout << "error: Image not found";
	}
	if (!playerTextures[3][0].loadFromFile("sprites/knightDown1.png"))
	{
		std::cout << "error: Image not found";
	}
	if (!playerTextures[3][1].loadFromFile("sprites/knightDown2.png"))
	{
		std::cout << "error: Image not found";
	}
	if (!playerTextures[3][2].loadFromFile("sprites/knightDown3.png"))
	{
		std::cout << "error: Image not found";
	}

	// terrain textures
	sf::Texture wallTexture;
	if (!wallTexture.loadFromFile("sprites/Wall.png"))
	{
		std::cout << "error: Image not found";
	}

	sf::Texture wallShadowTexture;
	if (!wallShadowTexture.loadFromFile("sprites/WallShadow.png"))
	{
		std::cout << "error: Image not found";
	}

	sf::Texture floorTexture;
	if (!floorTexture.loadFromFile("sprites/Floor.png"))
	{
		std::cout << "error: Image not found";
	}

	sf::Texture blankTexture;
	if (!blankTexture.loadFromFile("sprites/Blank.png"))
	{
		std::cout << "error: Image not found";
	}

	sf::Sprite dungeonMapLayout[dungeonDisplay][dungeonDisplay];

	for (int y = 0; y < dungeonDisplay; y++)
	{
		for (int x = 0; x < dungeonDisplay; x++) {
			dungeonMapLayout[y][x].setPosition(sf::Vector2f((float)(x * spriteSize), (float)(y * spriteSize)));
		}
	}

	enum characterDirection lastDirection = DOWN;
	int spriteCycle = 0;
	int idle = 0;
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
			lastDirection = LEFT;
			if (displayedSection[displayCenter][displayCenter - 1] == 0xe0)
			{
				playerLocation.x--;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			lastDirection = RIGHT;

			if (displayedSection[displayCenter][displayCenter + 1] == 0xe0)
			{
				playerLocation.x++;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			lastDirection = UP;

			if (displayedSection[displayCenter - 1][displayCenter] == 0xe0)
			{
				playerLocation.y--;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			lastDirection = DOWN;

			if (displayedSection[displayCenter + 1][displayCenter] == 0xe0)
			{
				playerLocation.y++;
			}
		}
		else
		{
			spriteCycle = 0;
		}
		if (++spriteCycle >= 3)
		{
			spriteCycle = 0;
		}


		window.clear();
		//std::cout << "\n";
		for (int y = 0; y < dungeonDisplay; y++)
		{
			for (int x = 0; x < dungeonDisplay; x++) {
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
		if (lastDirection == DOWN) {
			dungeonMapLayout[displayCenter][displayCenter].setTexture(playerTextures[3][spriteCycle]);
		}
		else if (lastDirection == RIGHT)
		{
			dungeonMapLayout[displayCenter][displayCenter].setTexture(playerTextures[1][spriteCycle]);
		}
		else if (lastDirection == LEFT)
		{
			dungeonMapLayout[displayCenter][displayCenter].setTexture(playerTextures[0][spriteCycle]);
		}
		else if (lastDirection == UP)
		{
			dungeonMapLayout[displayCenter][displayCenter].setTexture(playerTextures[2][spriteCycle]);
		}
		window.draw(dungeonMapLayout[displayCenter][displayCenter]);
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
